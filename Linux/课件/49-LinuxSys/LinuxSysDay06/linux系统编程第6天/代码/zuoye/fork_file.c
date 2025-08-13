#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int fd = open("./test.log", O_RDWR | O_CREAT, 0777);
	if(fd<0)
	{
		perror("open error");
		return -1;
	}

	pid_t pid;
	pid = fork();
	if(pid<0)
	{
		perror("fork error");
		return -1;
	}
	else if(pid>0) //父进程
	{
		printf("father: fpid==[%d], cpid==[%d]\n", getpid(), pid);
		write(fd, "hello world", strlen("hello world"));
		close(fd);
	}
	else if(pid==0) //子进程
	{
		printf("child: fpid==[%d], cpid==[%d]\n", getppid(), getpid());
		char buf[255];
		int n;
		memset(buf, 0x00, sizeof(buf));
		sleep(1);
		lseek(fd, 0, SEEK_SET);
		n = read(fd, buf, sizeof(buf));
		printf("read over, n==[%d], buf==[%s]\n", n, buf);
		close(fd);
	}


	return 0;
}
