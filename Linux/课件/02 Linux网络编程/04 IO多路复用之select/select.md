# 什么是I/O多路复用

**I/O 多路复用**(I/O Multiplexing)是一种让单个进程/线程能够同时监控多个I/O描述符（如socket、文件、管道等）的机制。当某个描述符就绪（可读、可写或出现异常）时，系统会通知程序进行相应的处理。

在传统阻塞I/O情况下，服务器不能同时处理多个连接，虽然我们使用多进程/线程实现了高并发服务器，但是只适用并发量小的网络应用开发，不适用并发量大的应用，因为会为每请求分配一个处理进程（线程）去响应，系统开销大。

而使用I/O多路复用，可以让一个进程或线程处理多个连接，减少了系统开销并提高了效率！

多路复用主要有三种技术：select，poll，epoll。epoll是最新的, 也是目前最好的多路复用技术。

# select

select模型是对简单C/S模型的优化，他解决了accept函数阻塞等待连接的问题。并且允许应用程序同时监视多个套接字，从而实现简单的并发请求。通过调用select函数确认一个或多个套接字当前的状态，并根据当前状态进行相应操作。在select模型模型中，select函数是最关键的。

## 工作原理

select模型维护了一个Socket数组，通过遍历该数组检查当前是否存在就绪socket，并将所有就绪的socket返回。我们遍历该数组提供相应服务。工作原理大致如下：

1. 将服务端Socket添加至socket数组中。
2. 调用select()函数遍历socket数组。
3. 返回就绪socket数组，对该数组集中处理。
4. 如果是服务端Socket，调用accept()函数接收连接请求，并将该客户端数组添加至socket数组。
5. 如果是客户端Socket，调用send()、recv()函数进行通信，当客户端下线时，从socket数组中移除该Socket。
6. 重复执行2-6步。

## 使用步骤

1. 启动Socket服务
2. 创建套接字
3. 为套接字绑定端口信息
4. 监听套接字
5. 使用select模型监听套接字集合，处理数据
6. 关闭套接字和网络服务

## select函数

> 需要包含sys/select.h头文件

函数原型如下：

```cpp
int select(int nfds, fd_set* readfds, fd_set* writefds, 
          fd_set* exceptfds, const struct timeval* timeout);
```

**参数**

- nfds：以上三个集合中最大的文件描述符数值 + 1，例如集合是{0,1,5,10}，那么 maxfd 就是 11
- readfds：内核检测该集合中的IO是否可读。如果想让内核帮忙检测某个IO是否可读，需要手动把文件描述符加入该集合。
- writefds：内核检测该集合中的IO是否可写。同readfds，需要手动把文件描述符加入该集合。但是只要建立连接任何时候都可写入，所以传NULL即可。
- exceptfds：内核检测该集合中的IO是否异常。同readfds，需要手动把文件描述符加入该集合。
- timeout：用户线程调用select的超时时长。
  - 设置成NULL，表示如果没有 I/O 事件发生，则 select 一直等待下去。
  - 设置为非0的值，这个表示等待固定的一段时间后从 select 阻塞调用中返回。
  - 设置成 0，表示根本不等待，检测完毕立即返回。

> 如果是服务端socket套接字，可读表示当前有客户端进行连接。如果是客户端套接字，可读表示当前有数据发送至服务端。select()函数是一个阻塞函数，如果指定了超时时间且没有socket就绪，select()函数返回。

**返回值**

- 大于0：成功，返回集合中已就绪的IO总个数
- 等于-1：调用失败
- 等于0：没有就绪的IO

从上述的select函数声明可以看出，fd_set本质是一个数组，为了方便我们操作该数组，操作系统提供了以下函数：

```c
// 将文件描述符fd从set集合中删除 
void FD_CLR(int fd, fd_set *set); 

// 判断文件描述符fd是否在set集合中 
int  FD_ISSET(int fd, fd_set *set); 

// 将文件描述符fd添加到set集合中 
void FD_SET(int fd, fd_set *set); 

// 将set集合中, 所有文件描述符对应的标志位设置为0
void FD_ZERO(fd_set *set);
```

[(86 封私信 / 87 条消息) IO多路复用——深入浅出理解select、poll、epoll的实现 - 知乎](https://zhuanlan.zhihu.com/p/367591714)

[三-select模型 - 西兰花战士 - 博客园](https://www.cnblogs.com/BroccoliFighter/p/17876823.html)

[12. 深入了解select、poll、epoll之间的区别 — [野火\]Linux基础与应用开发实战指南——基于LubanCat-全志系列板卡 文档](https://doc.embedfire.com/linux/h618/linux_base/zh/latest/system_programing/socket_io/socket_io.html)

## select模型实例

### 服务器

#### 基础代码

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

#### select模型代码

+ 然后添加select模型代码

```c
 //创建保存所有socket描述符的集合
        fd_set allFds;
        FD_ZERO(&allFds);       //初始化集合
        FD_SET(fd,&allFds);     //将监听套接字添加到集合中

        int maxFd = fd;
        char buffer[BUFSIZ + 1];

        //事件循环
        while(1) {

                fd_set readFds = allFds;                //拷贝监听描述符集合

                struct timeval tv = {5,0};              //超时时间，必须再循环中定义
                int nfds = select(maxFd + 1,&readFds,NULL,NULL,&tv);
                printf("nfds:%d\n",nfds);

                //失败
                if(nfds == -1) {
                        perror("select error");
                        exit(-1);
                }
                //超时(没有就绪的socket)
                else if(nfds == 0) {
                        continue;
                }
                //有就绪的socket
                else{
                        //有监听描述符
                        if(FD_ISSET(fd,&readFds)){
                                int newSocket = hdy_accept(fd,NULL,NULL);
                                if(newSocket < 0) {
                                }
                                else{
                                        printf("New connection:%d\n",newSocket);
                                        FD_SET(newSocket,&allFds);
                                        //如果新的连接的描述符大于最大描述符，则修改一下maxFd
                                        if(newSocket > maxFd) {
                                                maxFd = newSocket;
                                        }
                                }
                        }

                        //其他客户端描述符
                        for(int sockfd = fd + 1;sockfd < maxFd + 1;sockfd++) {
                                if(FD_ISSET(sockfd,&readFds)) {
                                        //读取数据
                                        int nread = hdy_read(sockfd,buffer,BUFSIZ);
                                        if(nread <=0) {
                                                close(sockfd);
                                                FD_CLR(sockfd,&allFds);
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
```

#### 代码优化

在上面的代码中，最后我们遍历客户端的描述符号时，是直接遍历到了maxFd，但是如果maxFd之前的很多客户端都关闭了，那么继续遍历这些已经关闭的描述符就非常浪费了！

```c
for(int i = fd + 1;i < maxFd + 1;i++);
```

我们可以将除了监听描述符之外的其他描述符用数组保存起来，然后直接遍历我们的有效描述符数组即可！

##### 自定义FD_LIST

+ 我们先来定义一个fd_list结构，提供一些宏来操作它

```c
/*描述符列表*/
typedef struct fd_list{
        int fds[1024];
        int size;
}fd_list;

/*描述符列表初始化*/
#define FD_LIST_INIT(list)\
        (list)->size = 0;\
        for(int i =0;i<1024;i++) {\
                (list)->fds[i] = -1;\
        }
/*将描述符添加到列表中*/
#define FD_LIST_SET(fd,list)\
        for(int i =0;i < 1024;i++) {\
                if((list)->fds[i] == -1) {\
                        (list)->fds[i] = fd;\
                        (list)->size++;\
                        break;\
                }\
        }

static int __fd_list_islist(int fd,fd_list* list) {
        for(int i =0;i < 1024;i++) {
                if((list)->fds[i] == fd) {
                        return 1;
                }
        }
        return 0;
}
/*判断描述符是否在列表中*/
#define FD_LIST_ISSET(fd,list) __fd_list_islist(fd,list)

/*将描述符从列表中删除掉*/
#define FD_LIST_CLR(fd,list)\
        for(int i =0;i < 1024;i++) {\
                if((list)->fds[i] == fd) {\
                        (list)->fds[i] = -1;\
                        (list)->size--;\
                        break;\
                }\
        }

/*遍历所有有效描述符*/
#define FD_LIST_FOR(var,list)\
        for(int _i = 0,_cnt = 0,_n = 0;_i < 1024;_i++,_cnt = 0)\
                if((list)->fds[_i] !=-1 && _n < (list)->size)\
                        for(var = (list)->fds[_i];_cnt<1;_cnt++,_n++)
```

##### 在select模型代码中使用

+ 先在循环之前定义并初始化

```c
fd_list clients;
FD_LIST_INIT(&clients);
```

+ 然后在客户端连接时，将描述符保存到列表中，断开链接或失败时，从列表中移除。

```c
//有就绪的socket
else{
        //有监听描述符
        if(FD_ISSET(fd,&readFds)){
                int newSocket = hdy_accept(fd,NULL,NULL);
                if(newSocket < 0) {
                }
                else{
                        printf("New connection:%d\n",newSocket);
                        FD_SET(newSocket,&allFds);
                    	//将新的描述符添加到列表中
                        FD_LIST_SET(newSocket,&clients);
                        printf("set clients size is:%d\n",clients.size);
                        //如果新的连接的描述符大于最大描述符，则修改一下maxFd
                        if(newSocket > maxFd) {
                               maxFd = newSocket;
                        }
                }

        //其他客户端描述符
        //for(int i = fd + 1;i < maxFd + 1;i++) {
        //直接使用遍历宏来进行遍历
        FD_LIST_FOR(int sockfd,&clients){
                if(FD_ISSET(sockfd,&readFds)) {
                        //读取数据
                        int nread = hdy_read(sockfd,buffer,BUFSIZ);
                        if(nread <=0) {
                                close(sockfd);
                                FD_CLR(sockfd,&allFds);
                                //将描述符从列表中移除掉
                                FD_LIST_CLR(sockfd,&clients);
                                printf("clr clients size is:%d\n",clients.size);
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
```

### 客户端代码

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
#include <sys/select.h>

int connectToServer(const char* ip,uint16_t port)
{
        //1,创建socket
        int fd = hdy_socket(AF_INET,SOCK_STREAM,0);

        //2,指定服务器IP地址和端口号
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        //addr.sin_addr.s_addr = INADDR_ANY;
        if(1!=inet_pton(AF_INET,ip,&addr.sin_addr)) {
                perror("inet_pton error");
                return -1;
        }

        hdy_connect(fd,(struct sockaddr*)(&addr),sizeof(addr));

        printf("connect server success ...\n");
        return fd;
}

int main(int argc,char* argv[])
{
        char ip[32] = "127.0.0.1";
        uint16_t port = 8080;
        if(argc < 3) {
                printf("Usage:%s host prot\n",argv[0]);
        }
        else{
                strcpy(ip,argv[1]);
                uint16_t _port = atoi(argv[2]);
                if(_port != 0) {
                        port = _port;
                }
        }

        int fd = connectToServer(ip,port);


        //创建保存所有socket描述符的集合
        fd_set allFds;
        FD_ZERO(&allFds);       //初始化集合
        FD_SET(fd,&allFds);     //将监听套接字添加到集合中

        int maxFd = fd;
        char buffer[BUFSIZ + 1];

        hdy_write(fd,"hello world",13);

        //事件循环
        while(1) {
                fd_set readFds = allFds;                //拷贝监听描述符集合

                struct timeval tv = {5,0};              //超时时间，必须再循环中定义
                int nfds = select(maxFd + 1,&readFds,NULL,NULL,&tv);

                //失败
                if(nfds == -1) {
                        perror("select error");
                        exit(-1);
                }
                //超时(没有就绪的socket)
                else if(nfds == 0) {
                        continue;
                }
                //有就绪的socket
                else{
                        //其他客户端描述符
                        if(FD_ISSET(fd,&readFds)) {
                                //读取数据
                                int nread = hdy_read(fd,buffer,BUFSIZ);
                                if(nread <=0) {
                                        close(fd);
                                        FD_CLR(fd,&allFds);
                                        break;
                                }
                                else{
                                        printf("msg is : %.*s\n",nread,buffer);
                                        for(int k = 0;k < nread/2;k++) {
                                                int idx = rand()%nread;
                                                buffer[idx] = tolower(buffer[idx]);
                                        }
                                        sleep(1);
                                        hdy_write(fd,buffer,nread);
                                }
                        }
                }
        }

        close(fd);
        return 0;
}
```

### 多线程结合select

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
#include <sys/select.h>
#include <pthread.h>

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

typedef struct fd_list{
        int fds[1024];
        int size;
}fd_list;

#define FD_LIST_INIT(list)\
        (list)->size = 0;\
        for(int i =0;i<1024;i++) {\
                (list)->fds[i] = -1;\
        }

#define FD_LIST_SET(fd,list)\
        for(int i =0;i < 1024;i++) {\
                if((list)->fds[i] == -1) {\
                        (list)->fds[i] = fd;\
                        (list)->size++;\
                        break;\
                }\
        }

static int __fd_list_islist(int fd,fd_list* list) {
        for(int i =0;i < 1024;i++) {
                if((list)->fds[i] == fd) {
                        return 1;
                }
        }
        return 0;
}

#define FD_LIST_ISSET(fd,list) __fd_list_islist(fd,list)

#define FD_LIST_CLR(fd,list)\
        for(int i =0;i < 1024;i++) {\
                if((list)->fds[i] == fd) {\
                        (list)->fds[i] = -1;\
                        (list)->size--;\
                        break;\
                }\
        }

#define FD_LIST_FOR(var,list)\
        for(int _i = 0,_cnt = 0,_n = 0;_i < 1024;_i++,_cnt = 0)\
                if((list)->fds[_i] !=-1 && _n < (list)->size)\
                        for(var = (list)->fds[_i];_cnt<1;_cnt++,_n++)

typedef struct State{
        fd_list clients;
        int maxFd;
        //创建保存所有socket描述符的集合
        fd_set allFds;
        pthread_mutex_t mutex;
}State;

void state_init(State* state)
{
        FD_LIST_INIT(&state->clients);
        FD_ZERO(&state->allFds);                        //初始化集合
        pthread_mutex_init(&state->mutex,NULL);
}

void state_destroy(State* state)
{
        pthread_mutex_destroy(&state->mutex);
}

void* select_thread_fn(void* arg)
{
        State* state = (State*)arg;
        char buffer[BUFSIZ + 1];

        //事件循环
        while(1) 
        {
                pthread_mutex_lock(&state->mutex);
                fd_set readFds = state->allFds;         //拷贝监听描述符集合
                pthread_mutex_unlock(&state->mutex);

                struct timeval tv = {5,0};              //超时时间，必须再循环中定义
                int nfds = select(state->maxFd + 1,&readFds,NULL,NULL,&tv);
                printf("nfds:%d\n",nfds);

                //失败
                if(nfds == -1) {
                        perror("select error");
                        exit(-1);
                }
                //超时(没有就绪的socket)
                else if(nfds == 0) {
                        continue;
                }
                //有就绪的socket
                else{
                        //其他客户端描述符
                        //for(int i = fd + 1;i < maxFd + 1;i++) {

                        pthread_mutex_lock(&state->mutex);
                        FD_LIST_FOR(int sockfd,&state->clients){
                                if(FD_ISSET(sockfd,&readFds)) {
                                        //读取数据
                                        int nread = hdy_read(sockfd,buffer,BUFSIZ);
                                        if(nread <=0) {
                                                close(sockfd);
                                                FD_CLR(sockfd,&state->allFds);
                                                FD_LIST_CLR(sockfd,&state->clients);
                                                printf("clr clients size is:%d\n",state->clients.size);
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
                        pthread_mutex_unlock(&state->mutex);
                }
                }
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

                State state={0};
                state_init(&state);


                //子线程使用select模型
                pthread_t thread;
                pthread_create(&thread,NULL,select_thread_fn,&state);
                pthread_detach(thread);

                //主线程接受新连接
                while(1) {
                        int newSocket = hdy_accept(fd,NULL,NULL);
                        if(newSocket < 0) {
                        }
                        else{
                                pthread_mutex_lock(&state.mutex);
                                printf("New connection:%d\n",newSocket);
                                FD_SET(newSocket,&state.allFds);
                                FD_LIST_SET(newSocket,&state.clients);
                                printf("set clients size is:%d\n",state.clients.size);

                                //如果新的连接的描述符大于最大描述符，则修改一下maxFd
                                if(newSocket > state.maxFd) {
                                        state.maxFd = newSocket;
                                }
                                pthread_mutex_unlock(&state.mutex);
                        }
                }

                close(fd);
                state_destroy(&state);
                return 0;
        }
```

