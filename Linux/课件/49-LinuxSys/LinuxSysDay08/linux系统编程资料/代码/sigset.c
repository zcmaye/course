//信号集相关函数测试
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
	signal(SIGQUIT, sighandler);

	//定义信号集变量
	sigset_t set;
	sigset_t oldset;

	//初始化信号集
	sigemptyset(&set);
	sigemptyset(&oldset);

	//将SIGINT SIGQUIT加入到set集合中
	sigaddset(&set, SIGINT);	
	sigaddset(&set, SIGQUIT);	

	//将set集合中的SIGINT SIGQUIT信号加入到阻塞信号集中
	//sigprocmask(SIG_BLOCK, &set, NULL);
	sigprocmask(SIG_BLOCK, &set, &oldset);

	int i=0;
	int j=1;
	sigset_t pend;
	
	while(1)
	{
		//获取未决信号集
		sigemptyset(&pend);
		sigpending(&pend);

		for(i=1; i<32; i++)
		{
			if(sigismember(&pend, i)==1)
			{
				printf("1");
			}
			else
			{
				 printf("0");
			}
		}	
		printf("\n");

		//循环10次解除对SIGINT SIGQUIT信号的阻塞
		if(j++%10==0)
		{
			//sigprocmask(SIG_UNBLOCK, &set, NULL);	
			sigprocmask(SIG_SETMASK, &oldset, NULL);
		}
		else
		{
			sigprocmask(SIG_BLOCK, &set, NULL);
		}

		sleep(1);
	}		

	return 0;
}
