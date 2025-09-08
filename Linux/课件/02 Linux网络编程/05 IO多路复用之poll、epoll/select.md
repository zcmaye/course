# poll

poll的实现和select非常相似，只是描述fd集合的方式不同。

poll改变了fds集合的描述方式，使用了pollfd结构而不是select的fd_set结构，使得poll支持的fds集合限制远大于select的1024。poll虽然解决了fds集合大小1024的限制问题，从实现来看。很明显它并没优化大量描述符数组被整体复制于用户态和内核态的地址空间之间，以及个别描述符就绪触发整体描述符集合的遍历的低效问题。poll随着监控的socket集合的增加性能线性下降，使得poll也并不适合用于大并发场景。

## poll函数

> 需要包含poll.h头文件

### 函数介绍

函数原型如下：

```cpp
struct pollfd {
　　 int fd;           /*文件描述符*/
　　 short events;     /*监控的事件*/
　　 short revents;    /*监控事件中满足条件返回的事件*/
};

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

**参数**

- fds：struct pollfd类型的数组, 存储了待检测的文件描述符，struct pollfd有三个成员：
  - fd：委托内核检测的文件描述符
  - events：委托内核检测的fd事件（输入、输出、错误），每一个事件有多个取值
  - revents：这是一个传出参数，数据由内核写入，存储内核检测之后的结果

- nfds：描述的是数组 fds 的大小
- timeout：用户线程调用poll的超时时长。
  - -1：一直阻塞，直到检测的集合中有就绪的IO事件，然后解除阻塞函数返回
  - 0：不阻塞，不管检测集合中有没有已就绪的IO事件，函数马上返回
  - 大于0：表示 poll 调用方等待指定的毫秒数后返回

**返回值**

- 大于0：成功，返回集合中已就绪的IO总个数
- 等于-1：调用失败
- 等于0：没有就绪的IO

### 事件标志

这些标志在 `events` 和 `revents` 中都可以使用，但有些标志只会在 `revents` 中出现。

#### 可读性事件 (Readability)

- `POLLIN`: 有数据可读。这是最常用的读事件。
  - 对于 TCP socket：意味着有数据到达（普通数据或带外数据），或者监听 socket 上有新的连接请求（`accept`）。
  - 对于管道/FIFO：写入端未关闭，且有数据可读。
  - 对于终端设备/标准输入：有输入。
- `POLLPRI`: 有高优先级数据可读（也称为带外数据，OOB）。例如，TCP socket 的紧急数据（URGENT data）。

#### 可写性事件 (Writability)

- `POLLOUT`: 可以写入数据而不被阻塞。
  - 对于 TCP socket：发送缓冲区有空间，可以写入数据。
  - 对于管道/FIFO：读取端未关闭，且管道有空间写入。

#### 错误/异常事件

- `POLLERR`: 设备发生错误。**这个事件只能在 `revents` 中被返回，而不能设置在 `events` 中**。例如，一个非法的操作（如对一个只读的文件描述符进行写操作）。
- `POLLHUP`: 挂起。连接已断开或通道的另一端已关闭。**注意**：在 `poll` 中，`POLLHUP` 和 `POLLIN` 可能会同时出现，表示“对端关闭连接，你还可以读取剩余的数据（读到 0）”。
- `POLLNVAL`: 无效的请求。文件描述符 `fd` 未打开。**这个事件也只能在 `revents` 中被返回**。

## poll模型实例

### 基础代码

+ 首先，按照常规服务的方式创建socket，绑定地址和端口号，并监听。

```c
#include "socket_wrap.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

uint16_t PORT = 8080;

int createServer()
{
        //1,创建socket
        int fd = hdy_socket(AF_INET,SOCK_STREAM,0);

        //设置socket选项
        int optval = 1;
        setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));  //地址重用
        setsockopt(fd,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof(optval));  //端口重用

        //2,绑定IP地址和端口号
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = INADDR_ANY;

        hdy_bind(fd,(struct sockaddr*)(&addr),sizeof(addr));

        //3,监听
        hdy_listen(fd,5);

        printf("server listen on port %d ...\n",PORT);
        return fd;
}

int main(int argc,char* argv[])
{
        if(argc < 2) {
                printf("Usage:%s prot\n",argv[0]);
        }
        else{
                uint16_t port = atoi(argv[1]);
                if(port != 0) {
                        PORT = port;
                }
        }

        int fd = createServer();
    	//这里实现select模型代码


        close(fd);
        return 0;
}
```

### poll模型代码

+ 然后添加select模型代码

```c
#include "socket_wrap.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

uint16_t PORT = 8080;

int createServer()
{
        //1,创建socket
        int fd = hdy_socket(AF_INET,SOCK_STREAM,0);

        //设置socket选项
        int optval = 1;
        setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));  //地址重用
        setsockopt(fd,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof(optval));  //端口重用

        //2,绑定IP地址和端口号
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = INADDR_ANY;

        hdy_bind(fd,(struct sockaddr*)(&addr),sizeof(addr));

        //3,监听
        hdy_listen(fd,5);

        printf("server listen on port %d ...\n",PORT);
        return fd;
}

int main(int argc,char* argv[])
{
        if(argc < 2) {
                printf("Usage:%s prot\n",argv[0]);
        }
        else{
                uint16_t port = atoi(argv[1]);
                if(port != 0) {
                        PORT = port;
                }
        }

        int fd = createServer();

        //创建pollfd数组
        struct pollfd fds[BUFSIZ];
        //初始化数据
        for(int i = 0;i<BUFSIZ;i++) {
                fds[i].fd = -1;
                fds[i].events = POLLIN;
        }
        fds[0].fd = fd;

        int maxFd = 0;
        char buffer[BUFSIZ + 1];

        //事件循环
        while(1) {

                int nfds = poll(fds,maxFd + 1,-1);
                printf("nfds:%d\n",nfds);

                //失败
                if(nfds == -1) {
                        perror("poll error");
                        exit(-1);
                }
                //超时(没有就绪的socket)
                else if(nfds == 0) {
                        continue;
                }
                //有就绪的socket
                else{
                        //有监听描述符
                        if(fds[0].revents & POLLIN){
                                int newSocket = hdy_accept(fd,NULL,NULL);
                                if(newSocket < 0) {
                                }
                                else{
                                        printf("New connection:%d\n",newSocket);
                                        for(int i = 1;i<BUFSIZ;i++) {
                                                if(fds[i].fd == -1) {
                                                        fds[i].fd = newSocket;
                                                        //如果新的连接的下标大于当前最大下标，则修改一下maxFd
                                                        if(i > maxFd) {
                                                                maxFd = i;
                                                        }
                                                        break;
                                                }
                                        }
                                }
                        }

                        //其他客户端描述符
                        for(int i = 1;i < maxFd + 1;i++) {
                                struct pollfd * pfd = fds + i;
                                if(pfd->revents & POLLIN){
                                        //读取数据
                                        int nread = hdy_read(pfd->fd,buffer,BUFSIZ);
                                        if(nread <=0) {
                                                close(pfd->fd);
                                                pfd->fd = -1;
                                        }
                                        else{
                                                for(int k = 0 ;k < nread/2;k++) {
                                                        int idx = rand()%nread;
                                                        buffer[idx] = toupper(buffer[idx]);
                                                }
                                                hdy_write(pfd->fd,buffer,nread);
                                        }
                                }
                        }
                }
        }

        close(fd);
        return 0;
}
```

# epoll

在linux的网络编程中，很长的时间都在使用select来做事件触发。在linux新的内核中，有了一种替换它的机制，就是epoll。相比于select，epoll最大的好处在于它不会随着监听fd数目的增长而降低效率。

> eventpoll 内部使用的是红黑树。通过红黑树来管理用户主进程accept添加进来的所有 socket 连接。红黑树具有良好的效率，它可在 O(logN) 时间内完成查找、增加、删除等操作。

## epoll函数

> 需要包含sys/epoll.h头文件

epoll模型需要使用三个函数：

- epoll_create：创建一个epoll句柄
- epoll_ctl：向 epoll 对象中添加/修改/删除要管理的连接
- epoll_wait：等待其管理的连接上的 IO 事件

### **epoll_create** 

`epoll_create`函数用于创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大。这个参数不同于select()中的第一个参数，给出最大监听的fd+1的值。需要注意的是，当创建好epoll句柄后，它就是会占用一个fd值，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。

```c
int epoll_create(int size);
```

**参数size:** 用来告诉内核这个监听的数目一共有多大，参数 size 并不是限制了 epoll 所能监听的描述符最大个数，只是对内核初始分配内部数据结构的一个建议。自从 linux 2.6.8 之后，size 参数是被忽略的，也就是说可以填只有大于 0 的任意值。

**返回值：**成功，返回poll 专用的文件描述符，失败，返回-1。

### epoll_ctl

epoll 的事件注册函数，它不同于 select() 是在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型。

```c
  int epoll_ctl(int epfd, int op, int fd,
               struct epoll_event *_Nullable event);
```

**参数：**

+ epfd：epoll描述符，使用`epoll_create`创建的那个。

+ op：表示动作，用三个宏来表示：
  + EPOLL_CTL_ADD：注册新的 fd 到 epfd 中；
  + EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
  + EPOLL_CTL_DEL：从 epfd 中删除一个 fd；

+ fd：要操作（注册、修改、删除）的描述符

+ event：告诉内核要监听什么事件，struct epoll_event 结构如:

  ```c
  struct epoll_event {
      uint32_t      events;  /* Epoll events */
      epoll_data_t  data;    /* User data variable */
  };
  union epoll_data {
      void     *ptr;
      int       fd;
      uint32_t  u32;
      uint64_t  u64;
  };
  typedef union epoll_data  epoll_data_t;
  ```

  + events可以是以下几个宏的集合：
    + EPOLLIN ：表示对应的文件描述符可以读（包括对端 SOCKET 正常关闭）；
    + EPOLLOUT：表示对应的文件描述符可以写；
    + EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
    + EPOLLERR：表示对应的文件描述符发生错误；
    + EPOLLHUP：表示对应的文件描述符被挂断；
    + EPOLLRDHUP：对方关闭连接或者半关闭连接
    + EPOLLET ：将 EPOLL 设为边缘触发(Edge Trigger)模式，这是相对于水平触发(Level Trigger)来说的。
    + EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个 socket 的话，需要再次把这个 socket 加入到 EPOLL 队列里

**返回值：**0表示成功，-1表示失败。

### epoll_wait

`epoll_wait`等待事件的产生，收集在 epoll 监控的事件中已经发送的事件，类似于 select() 调用。

```c
int epoll_wait(int epfd, struct epoll_event *events,
               int maxevents, int timeout);
```

**参数：**

+ epfd：epoll描述符，使用`epoll_create`创建的那个。
+ events：分配好的 epoll_event 结构体数组，epoll 将会把发生的事件赋值到events 数组中（events 不可以是空指针，内核只负责把数据复制到这个 events 数组中，不会去帮助我们在用户态中分配内存）。

+ maxevents： maxevents 告之内核这个 events 有多少个 。
+ timeout：用户线程超时时长。
  + -1：一直阻塞，直到检测的集合中有就绪的IO事件，然后解除阻塞函数返回
  + 0：不阻塞，不管检测集合中有没有已就绪的IO事件，函数马上返回
  + 大于0：表示 epoll_wait 调用方等待指定的毫秒数后返回

**返回值：**

+ 如果成功，表示返回需要处理的事件数目

+ 如果返回0，表示已超时

+ 如果返回-1，表示失败

## epoll模型示例

基础代码和select或poll一样，不再贴出！

```c
#include "socket_wrap.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAX_EVENT_NUM 10000

uint16_t PORT = 8080;

int createServer()
{
        //1,创建socket
        int fd = hdy_socket(AF_INET,SOCK_STREAM,0);

        //设置socket选项
        int optval = 1;
        setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));  //地址重用
        setsockopt(fd,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof(optval));  //端口重用

        //2,绑定IP地址和端口号
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = INADDR_ANY;

        hdy_bind(fd,(struct sockaddr*)(&addr),sizeof(addr));

        //3,监听
        hdy_listen(fd,5);

        printf("server listen on port %d ...\n",PORT);
        return fd;
}

int main(int argc,char* argv[])
{
        if(argc < 2) {
                printf("Usage:%s prot\n",argv[0]);
        }
        else{
                uint16_t port = atoi(argv[1]);
                if(port != 0) {
                        PORT = port;
                }
        }

        printf("EPOLLIN(%d),EPOLLOUT(%d), EPOLLRDHUP(%d),EPOLLHUP(%d),EPOLLERR(%d)\n",EPOLLIN,EPOLLOUT,EPOLLRDHUP , EPOLLHUP , EPOLLERR);

        int fd = createServer();

        //创建epoll实例
        int epfd = epoll_create(5);
        if(epfd == -1) {
                perror("epoll create error");
                return -1;
        }

        //给监听描述符创建事件
        struct epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;//设置该句柄为边缘触发（数据没处理完后续不会再触发事件，水平触发是不管数据有没有触发都返回事件）

        //将监听描述符添加到epoll中
        if(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event) == -1) {
                perror("epoll ctl error");
                return -1;
        }

        char buffer[BUFSIZ + 1];
        struct epoll_event events[MAX_EVENT_NUM];

        //事件循环
        while(1) {

                int nfds = epoll_wait(epfd,events,MAX_EVENT_NUM,-1);
                printf("nfds:%d\n",nfds);

                //失败
                if(nfds == -1) {
                        perror("poll error");
                        exit(-1);
                }
                //超时(没有就绪的socket)
                else if(nfds == 0) {
                        continue;
                }
                //有就绪的socket
                else{
                        for(int i =0;i<nfds;i++) {
                                int sockfd = events[i].data.fd;
                                //监听描述符(有客户端连接)
                                if(sockfd == fd) {
                                        int newSocket = hdy_accept(fd,NULL,NULL);
                                        if(newSocket < 0) {
                                        }
                                        else{
                                                printf("New connection:%d\n",newSocket);
                                                struct epoll_event event;
                                                event.data.fd = newSocket;
                                                event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;//设置该句柄为边缘触发（数据没处理完后续不会再触发事件，水平触发是不管数据有没有触发都返回事件）
                                                epoll_ctl(epfd,EPOLL_CTL_ADD,newSocket,&event);
                                        }
                                }
                                else if(events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                                        printf("EPOLLRDHUP | EPOLLHUP | EPOLLERR\n");
                                        printf("%d  EPOLLRDHUP(%d),EPOLLHUP(%d),EPOLLERR(%d)\n",events[i].events ,EPOLLRDHUP , EPOLLHUP , EPOLLERR);
                                        //将描述符从epoll中移除掉
                                        epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
                                        close(sockfd);
                                }
                                //处理客户端连接上收到数据
                                else if(events[i].events & EPOLLIN) {
                                        printf("EPOLLIN\n");
                                        //读取数据
                                        int nread = hdy_read(sockfd,buffer,BUFSIZ);
                                        if(nread <=0) {
                                                printf("quit~\n");
                                                close(sockfd);
                                        }
                                        else{
                                                for(int k = 0 ;k < nread/2;k++) {
                                                        int idx = rand()%nread;
                                                        buffer[idx] = toupper(buffer[idx]);
                                                }
                                                hdy_write(sockfd,buffer,nread);
                                        }
                                }

                        }
                }
        }

        close(epfd);
        close(fd);
        return 0;
}
```

## 通知触发模式

epoll是一种高效的IO事件通知机制，它支持两种触发模式：水平触发（LT, Level-Triggered）和边缘触发（ET, Edge-Triggered）。理解这两种模式的区别对于开发高性能的网络服务至关重要。

### 水平触发(LT)

在水平触发模式下，只要被监控的文件描述符上有可读写事件发生，epoll就会不断地通知应用程序，直到所有数据被处理完毕。这意味着，即使应用程序没有一次性读取或写入所有数据，epoll仍会在下一次调用*epoll_wait()*时再次通知应用程序。这种模式的优点是编程简单，不容易丢失事件，但可能会导致不必要的重复通知，影响性能。

> 水平触发是epoll的默认工作方式。

### 边缘触发(ET)

边缘触发模式则更高效，它只在文件描述符的状态发生变化时（例如从不可读变为可读）通知一次应用程序。这就要求应用程序必须立即处理所有事件，因为后续的*epoll_wait()*调用不会再次通知已经发生的事件。ET模式通常与**非阻塞IO**一起使用，以避免在读写操作中阻塞。这种模式的优点是减少了事件通知的次数，提高了性能，但要求程序必须更加小心地处理事件，以避免数据丢失。

设置描述符为非阻塞：

```c
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
```

有数据可读时，循环读取完数据(必须先设置描述符为非阻塞)。

```c
//处理客户端连接上收到数据
else if(events[i].events & EPOLLIN) {
        //读取数据
        int nread,total_read = 0;
        while((nread = hdy_read(sockfd,buffer,BUFFER_SIZE)) > 0) {
                for(int k = 0 ;k < nread/2;k++) {
                        int idx = rand()%nread;
                        buffer[idx] = toupper(buffer[idx]);
                }
                hdy_write(sockfd,buffer,nread);
                total_read +=nread;
        }
        if(nread  == -1) {
                //当设置描述符为非阻塞之后，没有数据可读了，错误码有可能会被设置为以下两个错误码
                if(errno == EAGAIN || errno == EWOULDBLOCK) {
                        // 这是正常情况：已经读取了所有可用数据
                        printf("Read all %d bytes of data\n", total_read);
                }
                else{
                        printf("quit~\n");
                        epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
                        close(sockfd);
                }
        }
        else if(nread == 0) {
                printf("quit~\n");
                epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
                close(sockfd);
        }
}
```



> 只要缓冲区的数据有变化，epoll_wait就会返回就绪。
>
> 这里的数据变化并不单纯指缓冲区从有数据变为没有数据，或者从没有数据变为有数据，还包括了数据变多或者变少。即当buffer长度有变化时，就会触发。
>
> 假设epoll被设置为了边缘触发，当客户端写入了100个字符，由于缓冲区从0变为了100，于是服务端epoll_wait触发一次就绪，服务端读取了2个字节后不再读取。这个时候再去调用epoll_wait会发现不会就绪，只有当客户端再次写入数据后，才会触发就绪。

### 使用场景

- **水平触发（LT）**：适用于需要分步处理或逐步读取数据的场景，如逐步解析HTTP请求头。
- **边缘触发（ET）**：适用于需要一次性读取或写入大量数据的场景，如文件传输。

- 在高并发场景下，边缘触发（ET）模式通常更受青睐，因为它减少了系统调用的次数，提高了性能。
- 对于监听socket（listenfd），通常使用水平触发（LT）模式，以确保不会错过任何连接请求。
