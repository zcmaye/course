//循环创建子线程,并且打印是第几个子线程
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

//线程执行函数
void *mythread(void *arg)
{
	int i = *(int *)arg;
	printf("[%d]:child thread, pid==[%d], id==[%ld]\n", i, getpid(), pthread_self());
	sleep(100);
}

int main()
{
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	//                      void *(*start_routine) (void *), void *arg);
	//创建子线程
	int ret;
	int i = 0;
	int n = 5;
	int arr[5];
	pthread_t thread[5];
	for(i=0; i<n; i++)
	{
		arr[i] = i;
		ret = pthread_create(&thread[i], NULL, mythread, &arr[i]);
		if(ret!=0)
		{
			printf("pthread_create error, [%s]\n", strerror(ret));
			return -1;
		}
	}
	printf("main thread, pid==[%d], id==[%ld]\n", getpid(), pthread_self());

	//目的是为了让子线程能够执行起来
	sleep(100);
	return 0;
}
