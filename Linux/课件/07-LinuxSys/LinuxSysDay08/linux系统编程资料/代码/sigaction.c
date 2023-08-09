//sigaction测试: 完成信号的注册
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

//信号处理函数
void sighandler(int signo)
{
	printf("signo==[%d]\n", signo);
	sleep(5);
}

int main()
{
	//注册SIGINT信号处理函数
	struct sigaction act;
	act.sa_handler = sighandler; //信号处理函数
	sigemptyset(&act.sa_mask); //阻塞的信号
	//sigaddset(&act.sa_mask, SIGQUIT); //在信号处理函数执行期间阻塞SIGQUIT信号
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);

	signal(SIGQUIT, sighandler);

	while(1)
	{
		sleep(1);	
	}
	return 0;
}
