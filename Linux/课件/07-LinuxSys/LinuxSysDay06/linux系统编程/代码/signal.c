//signal函数测试---注册信号处理函数
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

	//while(1)
	{
		sleep(10);
	}

	return 0;
}
