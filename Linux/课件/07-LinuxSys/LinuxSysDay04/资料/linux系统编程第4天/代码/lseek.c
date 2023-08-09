//lseek函数获取文件大小
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	//打开文件
	int fd = open(argv[1], O_RDWR);
	if(fd<0)
	{
		perror("open error");
		return -1;
	}

	//调用lseek函数获取文件大小
	int len = lseek(fd, 0, SEEK_END);
	printf("file size:[%d]\n", len);

	//关闭文件
	close(fd);

	return 0;
}
