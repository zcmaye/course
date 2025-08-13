//signal函数测试: 测试给没有读端的管道写数据, 会产生SIGPIPE信号
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//信号处理函数
void sighandler(int signo)
{
	printf("signo==[%d]\n", signo);
}

int main()
{
	//创建管道
	//int pipe(int pipefd[2]);
	int fd[2];
	int ret = pipe(fd);
	if(ret<0)
	{
		perror("pipe error");
		return -1;
	}

	//注册SIGPIPE信号处理函数
	signal(SIGPIPE, sighandler);

	//关闭读端
	close(fd[0]);

	write(fd[1], "hello world", strlen("hello world"));	


	return 0;
}
