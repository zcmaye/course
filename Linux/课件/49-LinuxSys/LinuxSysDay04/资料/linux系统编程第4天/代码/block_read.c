//验证read函数读设备文件是阻塞的
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	//读标准输入
	char buf[1024];
	memset(buf, 0x00, sizeof(buf));
	int n = read(STDIN_FILENO, buf, sizeof(buf));
	printf("FIRST: n==[%d], buf==[%s]\n", n, buf);

	return 0;
}
