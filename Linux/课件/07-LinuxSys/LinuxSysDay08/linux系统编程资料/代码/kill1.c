//kill函数测试: 父进程杀死子进程或者子进程杀死父进程
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int i = 0;

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
			//父进程杀死第一个子进程
			/*if(i==0)
			{
				kill(pid, SIGKILL);
			}*/
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

		//子进程杀死父进程
		//kill(getppid(), SIGKILL);

		sleep(1);
		//杀死同一组的所有进程
		kill(-1, SIGKILL);	
    }
    
    if(i==1)
    {
    	printf("the second child, pid==[%d]\n", getpid());
		sleep(10);
    }
    
    if(i==2)
    {
    	printf("the third child, pid==[%d]\n", getpid());
		sleep(10);
    }
    
    if(i==3)
    {
    	printf("the father, pid==[%d]\n", getpid());
		sleep(10);
    }

	return 0;
}
