//lseek函数实现文件拓展
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

	//移动文件指针到第100个字节处
	lseek(fd, 100, SEEK_SET);

	//进行一次写入操作
	write(fd, "H", 1);

	//关闭文件
	close(fd);

	return 0;
}
