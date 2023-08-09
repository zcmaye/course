#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

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
    }

	return 0;
}
