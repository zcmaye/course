//IO函数测试--->open close read write lseek
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
	int fd = open(argv[1], O_RDWR | O_CREAT, 0777);
	if(fd<0)
	{
		perror("open error");
		return -1;
	}

	//写文件
	//ssize_t write(int fd, const void *buf, size_t count);
	write(fd, "hello world", strlen("hello world"));

	//移动文件指针到文件开始处
	//off_t lseek(int fd, off_t offset, int whence);
	lseek(fd, 0, SEEK_SET);

	//读文件
	//ssize_t read(int fd, void *buf, size_t count);
	char buf[1024];
	memset(buf, 0x00, sizeof(buf));
	int n = read(fd, buf, sizeof(buf));
	printf("n==[%d], buf==[%s]\n", n, buf);

	//关闭文件
	close(fd);

	return 0;
}
