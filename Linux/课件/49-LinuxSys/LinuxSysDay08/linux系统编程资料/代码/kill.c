//kill函数测试
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	kill(getpid(), SIGKILL);

	printf("hello world\n");

	return 0;
}
