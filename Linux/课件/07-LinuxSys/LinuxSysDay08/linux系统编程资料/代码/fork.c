//验证SIGCHLD信号是如何产生的: 子进程退出, SIGSTOP, SIGCONT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int signo)
{
	printf("signo==[%d]\n", signo);
}

int main(int argc, char *argv[])
{
	pid_t pid;
	int i = 0;

	signal(SIGCHLD, sighandler);

	pid = fork();
	if(pid<0)
	{
		perror("fork error");
		return -1;
	}
	else if(pid>0)
	{
		printf("father process, pid==[%d], child pid==[%d]\n", getpid(), pid);	
		while(1)
		{
			sleep(1);
		}
	}
	else
	{
		printf("child process, father pid==[%d], pid==[%d]\n", getppid(), getpid());
		while(1)
		{
			sleep(1);
		}
	}

	return 0;
}
