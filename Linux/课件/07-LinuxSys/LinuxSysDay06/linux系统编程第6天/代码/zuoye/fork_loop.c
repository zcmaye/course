//调用fork函数创建子进程, 并完成对子进程的回收
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int i = 0;
	int n = 3;

	for(i=0; i<n; i++)	
	{
		//fork子进程
		pid_t pid = fork();
		if(pid<0) //fork失败的情况
		{
			perror("fork error");
			return -1;
		}
		else if(pid>0) //父进程
		{
			printf("father: fpid==[%d], cpid==[%d]\n", getpid(), pid);
			sleep(1);
		}
		else if(pid==0) //子进程
		{
			printf("child: fpid==[%d], cpid==[%d]\n", getppid(), getpid());
			break;
		}
	}

	//父进程
	if(i==3)
	{
		printf("[%d]:father: fpid==[%d]\n", i, getpid());
		pid_t wpid;
		int status;

		while(1)
		{
			wpid = waitpid(-1, &status, WNOHANG);
			if(wpid==0) // 没有子进程退出
			{
				continue;
			}			
			else if(wpid==-1) //已经没有子进程了
			{
				printf("no child is living, wpid==[%d]\n", wpid);
				exit(0);
			}
			else if(wpid>0) //有子进程退出
			{
				if(WIFEXITED(status))
				{
					printf("normal exit, status==[%d]\n", WEXITSTATUS(status));
				}
				else if(WIFSIGNALED(status))
				{
					printf("killed by signo==[%d]\n", WTERMSIG(status));
				}
			}
		}
	}

	//第1个子进程
	if(i==0)
	{
		printf("[%d]:child: cpid==[%d]\n", i, getpid());
		execlp("ls", "ls", "-l", NULL);
		perror("execl error");
		exit(-1);
	}

	//第2个子进程
	if(i==1)
	{
		printf("[%d]:child: cpid==[%d]\n", i, getpid());
		execl("/home/itcast/test/course/day6/0527/zuoye/hello", "hello", "1111", "2222", NULL);
		perror("execl error");
		return -1;
	}

	//第3个子进程
	if(i==2)
	{
		printf("[%d]:child: cpid==[%d]\n", i, getpid());
		execl("/home/itcast/test/course/day6/0527/zuoye/test", "test", NULL);
		perror("execl error");
		return -1;
	}

	return 0;
}
