//在创建子线程的时候设置分离属性
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

//线程执行函数
void *mythread(void *arg)
{
	printf("child thread, pid==[%d], id==[%ld]\n", getpid(), pthread_self());
	sleep(2);
}

int main()
{
	//定义pthread_attr_t类型的变量
	pthread_attr_t attr;
	
	//初始化attr变量
	pthread_attr_init(&attr);

	//设置attr为分离属性
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	//创建子线程
	pthread_t thread;
	int ret = pthread_create(&thread, &attr, mythread, NULL);
	if(ret!=0)
	{
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}
	printf("main thread, pid==[%d], id==[%ld]\n", getpid(), pthread_self());

	//释放线程属性
	pthread_attr_destroy(&attr);

	//验证子线程是否为分离属性
	ret = pthread_join(thread, NULL);
	if(ret!=0)
	{
		printf("pthread_join error:[%s]\n", strerror(ret));
	}

	return 0;
}
