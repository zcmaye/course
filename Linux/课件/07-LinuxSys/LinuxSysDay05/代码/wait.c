//父进程调用wait函数完成对子进程的回收
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

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
		printf("father: [%d], pid==[%d], fpid==[%d]\n", pid, getpid(),getppid());
		int status;
		pid_t wpid = wait(&status);
		printf("wpid==[%d]\n", wpid);
		if(WIFEXITED(status)) //正常退出
		{
			printf("child normal exit, status==[%d]\n", WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status)) //被信号杀死
		{
			printf("child killed by signal, signo==[%d]\n", WTERMSIG(status));
		}
		
	}
	else if(pid==0) //子进程
	{
		
		printf("child: pid==[%d], fpid==[%d]\n", getpid(), getppid());
		sleep(20);
		return 9;
	}

	return 0;
}
