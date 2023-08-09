//比较线程ID是否相等
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

	//比较线程ID
	//if(pthread_equal(thread, pthread_self())!=0)
	if(pthread_equal(pthread_self(), pthread_self())!=0)
	{
		printf("two thread id is same\n");
	}
	else
	{
		printf("two thread id is not same\n");
	}

	//目的是为了让子线程能够执行起来
	sleep(1);
	return 0;
}
