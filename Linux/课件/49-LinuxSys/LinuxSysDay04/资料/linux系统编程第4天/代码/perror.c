//测试perror函数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	//打开文件
	int fd = open(argv[1], O_RDWR);
	if(fd<0)
	{
		perror("open error");
		if(errno==ENOENT)
		{
			printf("same\n");
		}
		//return -1;
	}

	int n = 0;
	for(n=0; n<64; n++)
	{
		errno = n;
		printf("[%d]:[%s]\n", n, strerror(errno));
	}

	//关闭文件
	//close(fd);

	return 0;
}
