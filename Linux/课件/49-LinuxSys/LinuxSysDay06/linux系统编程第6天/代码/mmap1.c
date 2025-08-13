//使用mmap函数完成父子进程间通信
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	//使用mmap函数建立共享映射区
	//void *mmap(void *addr, size_t length, int prot, int flags,
    //              int fd, off_t offset);
	int fd = open("./test.log", O_RDWR);
	if(fd<0)
	{
		perror("open error");
		return -1;
	}

	int len = lseek(fd, 0, SEEK_END);

	void * addr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	//void * addr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(addr==MAP_FAILED)
	{
		perror("mmap error");
		return -1;
	}
	close(fd);

	//创建子进程
	pid_t pid = fork();
	if(pid<0) 
	{
		perror("fork error");
		return -1;
	}
	else if(pid>0)
	{
		memcpy(addr, "hello world", strlen("hello world"));	
		wait(NULL);
	}
	else if(pid==0)
	{
		sleep(1);
		char *p = (char *)addr;
		printf("[%s]", p);
	}

	return 0;
}
