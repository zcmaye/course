//alarm函数测试
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int signo)
{
	printf("signo==[%d]\n", signo);
}

int main()
{
	signal(SIGALRM, sighandler);

	//设置时钟
	int n = alarm(5);
	printf("n==[%d]\n", n);

	sleep(2);
	n = alarm(2);
	printf("n==[%d]\n", n);

	//取消时钟
	n = alarm(0);
	printf("n==[%d]\n", n);

	sleep(10);
	return 0;
}
