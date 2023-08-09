//验证read函数读普通文件是否阻塞
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

	//读文件
	char buf[1024];
	memset(buf, 0x00, sizeof(buf));
	int n = read(fd, buf, sizeof(buf));
	printf("FIRST: n==[%d], buf==[%s]\n", n, buf);

	//再次读文件, 验证read函数是否阻塞
	memset(buf, 0x00, sizeof(buf));
	n = read(fd, buf, sizeof(buf));
	printf("SECOND: n==[%d], buf==[%s]\n", n, buf);

	//关闭文件
	close(fd);

	return 0;
}
