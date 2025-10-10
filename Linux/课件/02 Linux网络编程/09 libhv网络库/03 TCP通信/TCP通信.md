## TCP通信

### 服务器

以`Tcp echo server`为例，使用libhv创建服务器。

```c
void on_read(hio_t* io, void* buf, int readbytes)
{
	printf("data is : %.*s\n", readbytes, (char*)buf);

	hio_write(io, buf, readbytes);
	//response_json(io, "{\"code\":200,\"msg\":\"ok\"}", 200);
}

void on_close(hio_t* io)
{
	printf("on_close,fd=%p\n", io);
}

void on_accept(hio_t* io)
{
	printf("on_accept,fd=%p\n", io);

	//设置读事件回调
	hio_setcb_read(io, on_read);

	//设置close事件回调
	hio_setcb_close(io, on_close);

	//开始读
	hio_read(io);
}

void test_tcp_server()
{
	//创建一个事件循环
	hloop_t* loop = hloop_new(0);

	//创建一个tcp服务器
	hio_t* server = hloop_create_tcp_server(loop, "0.0.0.0", 8080, on_accept);
	if (!server) {
		exit(-1);
	}

	//运行事件循环
	hloop_run(loop);

	//释放事件循环
	hloop_free(&loop);
}
```



### 客户端

```c
#include "hv/hloop.h"
#include "hv/htime.h"

void on_timer(htimer_t* timer) {
    char str[DATETIME_FMT_BUFLEN] = {0};
    datetime_t dt = datetime_now();
    datetime_fmt(&dt, str);

    printf("> %s\n", str);
    // 获取userdata
    hio_t* io = (hio_t*)hevent_userdata(timer);
    // 发送当前时间字符串
    hio_write(io, str, strlen(str));
}

void on_close(hio_t* io) {
}

void on_recv(hio_t* io, void* buf, int readbytes) {
    printf("< %.*s\n", readbytes, (char*)buf);
}

void on_connect(hio_t* io) {
    // 设置read回调
    hio_setcb_read(io, on_recv);
    // 开始读
    hio_read(io);

	// 添加一个定时器
    htimer_t* timer = htimer_add(hevent_loop(io), on_timer, 1000, INFINITE);
    // 设置userdata
    hevent_set_userdata(timer, io);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: cmd port\n");
        return -10;
    }
    int port = atoi(argv[1]);

	// 创建事件循环
    hloop_t* loop = hloop_new(0);
    // 创建TCP客户端
    hio_t* io = hloop_create_tcp_client(loop, "127.0.0.1", port, on_connect, on_close);
    if (io == NULL) {
        return -20;
    }
    // 运行事件循环
    hloop_run(loop);
    // 释放事件循环
    hloop_free(&loop);
    return 0;
}

```

