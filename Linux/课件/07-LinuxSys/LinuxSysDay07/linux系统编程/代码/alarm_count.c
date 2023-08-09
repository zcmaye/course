//测试1秒钟可以数多少数字
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	alarm(1);
	int i = 0;
	while(1)
	{
		printf("[%d]", i++);
	}

	return 0;
}
