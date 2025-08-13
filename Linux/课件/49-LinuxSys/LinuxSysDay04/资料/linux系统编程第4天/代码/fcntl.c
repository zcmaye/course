//修改文件描述符的flag属性
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

	//获得和设置fd的flags属性
	int flags = fcntl(fd, F_GETFL, 0);
	flags = flags | O_APPEND;
	fcntl(fd, F_SETFL, flags);

	//写文件
	write(fd, "hello world", strlen("hello world"));

	//关闭文件
	close(fd);

	return 0;
}
