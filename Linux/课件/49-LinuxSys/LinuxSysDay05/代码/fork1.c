//fork函数测试
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int g_var = 99;

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
		g_var++;
		printf("[%p]", &g_var);
	}
	else if(pid==0) //子进程
	{
		sleep(1); //为了避免父进程还没有执行, 子进程已经结束了
		printf("[%p]", &g_var);
		printf("child: pid==[%d], fpid==[%d]\n", getpid(), getppid());
		printf("child: g_var==[%d]\n", g_var);
	}
	
	return 0;
}
