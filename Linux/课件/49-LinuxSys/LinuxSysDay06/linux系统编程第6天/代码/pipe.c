#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	//创建管道
	//int pipe(int pipefd[2]);
	int fd[2];
	int ret = pipe(fd);
	if(ret<0)
	{
		perror("pipe error");
		return -1;
	}

	//创建子进程
	pid_t pid = fork();
	if(pid<0) 
	{
		perror("fork error");
		return -1;
	}
	else if(pid>0)
	{
		//关闭读端
		close(fd[0]);
		sleep(5);
		write(fd[1], "hello world", strlen("hello world"));	

		wait(NULL);
	}
	else 
	{
		//关闭写端
		close(fd[1]);
		
		char buf[64];
		memset(buf, 0x00, sizeof(buf));
		int n = read(fd[0], buf, sizeof(buf));
		printf("read over, n==[%d], buf==[%s]\n", n, buf);
	
	}

	return 0;
}
