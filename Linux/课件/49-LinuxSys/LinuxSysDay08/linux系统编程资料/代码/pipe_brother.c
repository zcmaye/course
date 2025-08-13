#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int fd[2];
	int ret;
	pid_t pid;

	//创建一个管道
	ret = pipe(fd);
	if(ret<0)
	{
		perror("pipe error");
		return -1;
	}

	int i = 0;
	int n = 2;
	for(i=0; i<n; i++)
	{
		//创建子进程
		pid = fork();
		if(pid<0)
		{
			perror("fork error");
			return -1;
		}
		else if(pid==0)
		{
			break;
		}

	}

	if(i==n)
	{
		close(fd[0]);	
		close(fd[1]);	

		pid_t wpid;
		int status;

		while(1)
		{
			//等待回收子进程
			wpid = waitpid(-1, &status, WNOHANG);	
			if(wpid==0) //没有子进程退出
			{
				sleep(1);
				continue;
			}
			else if(wpid==-1) //已经没有子进程
			{
				printf("no child is living, wpid==[%d]\n", wpid);
				exit(0);
			}
			else if(wpid>0)
			{
				if(WIFEXITED(status)) //正常退出
				{
					printf("child normal exited, status==[%d]\n", WEXITSTATUS(status));
				}
				else if(WIFSIGNALED(status)) //被信号杀死
				{
					 printf("child killed by signo==[%d]\n", WTERMSIG(status));
				}
			}
			
		}
	}
	
	//第一个子进程
	if(i==0)
	{
		
		close(fd[0]);

		//将标准输出重定向到管道到写端
        dup2(fd[1], STDOUT_FILENO);
		execlp("ps", "ps", "aux", NULL);

		//close(fd[1]);
	}

	//第二个子进程
	if(i==1)
	{
		printf("child: fpid==[%d], cpid==[%d]\n", getppid(), getpid());
		close(fd[1]);

		//将标准输入重定向到管道到读端
		dup2(fd[0], STDIN_FILENO);
		execlp("grep", "grep", "--color", "bash", NULL);

		//close(fd[0]);
	}

	return 0;
}
