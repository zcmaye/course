//sigaction函数测试---注册信号处理函数
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

//信号处理函数
void sighandler(int signo)
{
	printf("signo==[%d]\n", signo);
	sleep(4);
}

int main()
{
	//注册信号处理函数
	struct sigaction act;
	act.sa_handler = sighandler;
	sigemptyset(&act.sa_mask);  //在信号处理函数执行期间, 不阻塞任何信号
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);

	
	signal(SIGQUIT, sighandler);	

	while(1)
	{
		sleep(10);
	}

	return 0;
}
