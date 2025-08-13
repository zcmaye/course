//raise和abort函数测-
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

//信号处理函数
void sighandler(int signo)
{
	printf("signo==[%d]\n", signo);
}

int main()
{
	//注册信号处理函数
	signal(SIGINT, sighandler);

	//给当前进程发送SIGINT信号
	raise(SIGINT);

	//给当前进程发送SIGABRT
	abort();

	while(1)
	{
		sleep(10);
	}

	return 0;
}
