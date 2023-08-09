//设置子线程为分离属性
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
	sleep(10);
}

int main()
{
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //                      void *(*start_routine) (void *), void *arg);
	//创建子线程
	pthread_t thread;
	int ret = pthread_create(&thread, NULL, mythread, NULL);
	if(ret!=0)
	{
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}
	printf("main thread, pid==[%d], id==[%ld]\n", getpid(), pthread_self());

	//设置线程为分离属性
	pthread_detach(thread);

	//子线程设置分离属性,则pthread_join不再阻塞,立刻返回
	ret = pthread_join(thread, NULL);
	if(ret!=0)
	{
		printf("pthread_join error:[%s]\n", strerror(ret));
	}

	//目的是为了让子线程能够执行起来
	sleep(1);
	return 0;
}
