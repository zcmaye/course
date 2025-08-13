//使用SIGUSR1和SIGUSR2在父子进程间交替数数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int num = 0;
int flag;

void func1(int signo)
{
	printf("F:[%d]\n", num);
	num += 2;
	flag = 0;
	sleep(1);
}

void func2(int signo)
{
	printf("C:[%d]\n", num);
	num += 2;
	flag = 0;
	sleep(1);
}

int main(int argc, char *argv[])
{
	int ret;
	pid_t pid;
	
	pid = fork();
	if(pid<0)
	{
		perror("fork error");
		return -1;
	}
	else if(pid>0)
	{
		num=0;
		flag  = 1;
		signal(SIGUSR1, func1);	

		while(1)
		{
			if(flag==0)
			{
				kill(pid, SIGUSR2);
				flag = 1;
			}
		}
	}
	else if(pid==0)
	{
		num=1;
		flag = 0;
		signal(SIGUSR2, func2);

		while(1)
		{
			if(flag==0)
			{
				kill(getppid(), SIGUSR1);
				flag = 1;
			}
		}
	}
}

