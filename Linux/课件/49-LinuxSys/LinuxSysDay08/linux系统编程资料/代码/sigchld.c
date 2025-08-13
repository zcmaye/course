//父进程使用SIGCHLD信号完成对子进程的回收
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//SIGCHLD信号处理函数
void waitchild(int signo)
{
	pid_t wpid;

	while(1)
	{
		wpid = waitpid(-1, NULL, WNOHANG);
		if(wpid>0)
		{
			printf("child is quit, wpid==[%d]\n", wpid);
		}
		else if(wpid==0)
		{
			printf("child is living, wpid==[%d]\n", wpid);
			break;
		}
		else if(wpid==-1)
		{
			printf("no child is living, wpid==[%d]\n", wpid);
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;
	int i = 0;

	//将SIGCHLD信号阻塞
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);
	sigprocmask(SIG_BLOCK, &mask, NULL);

	for(i=0; i<3; i++)
	{
		pid = fork();
		if(pid<0)
		{
			perror("fork error");
			return -1;
		}
		else if(pid>0)
		{
			printf("father process, pid==[%d], child pid==[%d]\n", getpid(), pid);	
		}
		else
		{
			printf("child process, father pid==[%d], pid==[%d]\n", getppid(), getpid());
			break;
		}
	}

	if(i==0)
	{
		printf("the first child, pid==[%d]\n", getpid());
	}

	if(i==1)
	{
		printf("the second child, pid==[%d]\n", getpid());
	}

	if(i==2)
	{
		printf("the third child, pid==[%d]\n", getpid());
	}

	if(i==3)
	{
		printf("the father, pid==[%d]\n", getpid());

		//注册SIGCHLD信号处理函数
		struct sigaction act;
		act.sa_handler = waitchild;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		sleep(5);
		sigaction(SIGCHLD, &act, NULL);

		//完成SIGCHLD信号的注册后, 解除对SIGCHLD信号的阻塞
		sigprocmask(SIG_UNBLOCK, &mask, NULL);

		while(1)
		{
			sleep(1);
		}
	}

	return 0;
}
