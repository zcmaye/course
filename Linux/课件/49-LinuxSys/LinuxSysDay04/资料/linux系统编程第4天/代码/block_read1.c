//测试读设备文件是阻塞的
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	//读文件
	char buf[64];
	memset(buf, 0x00, sizeof(buf));
	int n = read(STDIN_FILENO, buf, sizeof(buf));
	printf("read, n==[%d], buf==[%s]\n", n, buf);

	return 0;
}
