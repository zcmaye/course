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

	//注册SIGINT和SIGQUIT的信号处理函数
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);

	//定义sigset_t类型的变量
	sigset_t pending, mask, oldmask;

	//初始化
	sigemptyset(&pending);
	sigemptyset(&mask);
	sigemptyset(&oldmask);

	//将SIGINT和SIGQUIT加入到阻塞信号集中
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);

	//将mask中的SIGINT和SIGQUIT信号加入到阻塞信号集中
	//sigprocmask(SIG_BLOCK, &mask, NULL);
	sigprocmask(SIG_BLOCK, &mask, &oldmask);

	int i = 1;
	int k = 1;
	while(1)
	{
		//获取未决信号集
		sigpending(&pending);	

		for(i=1; i<32; i++)
		{
			//判断某个信号是否在集合中
			if(sigismember(&pending, i)==1)	
			{
				printf("1");
			}
			else
			{
				printf("0");	
			}
		}
		printf("\n");

		if(k++%10==0)
		{
			//从阻塞信号集中解除对SIGINT和SIGQUIT的阻塞
			//sigprocmask(SIG_UNBLOCK, &mask, NULL);	
			sigprocmask(SIG_SETMASK, &oldmask, NULL);	
		}
		else
		{
			sigprocmask(SIG_BLOCK, &mask, NULL);	
		}

		sleep(1);
	}

	return 0;
}
