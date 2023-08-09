//孤儿进程
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	//创建子进程
	pid_t pid = fork();
	if(pid<0) //fork失败的情况
	{
		perror("fork error");
		return -1;
	}
	else if(pid>0)//父进程
	{
		sleep(5);
		printf("father: [%d], pid==[%d], fpid==[%d]\n", pid, getpid(),getppid());
	}
	else if(pid==0) //子进程
	{
		
		printf("child: pid==[%d], fpid==[%d]\n", getpid(), getppid());
		sleep(20);
		printf("child: pid==[%d], fpid==[%d]\n", getpid(), getppid());
	}
	

	return 0;
}
