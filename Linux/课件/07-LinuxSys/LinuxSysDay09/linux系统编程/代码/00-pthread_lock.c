#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//定义一把锁
pthread_mutex_t mutex;

void *mythread1(void *args)
{
	while(1)
	{
		//加锁
		pthread_mutex_lock(&mutex);

		printf("hello ");
		sleep(rand()%3);
		printf("world\n");
	
		//解锁
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}

	pthread_exit(NULL);
}


void *mythread2(void *args)
{
	while(1)
	{
		//加锁
		pthread_mutex_lock(&mutex);

		printf("HELLO ");
		sleep(rand()%3);
		printf("WORLD\n");

		//解锁
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}

	pthread_exit(NULL);
}

int main()
{
	int ret;
	pthread_t thread1;
	pthread_t thread2;

	//随机数种子
	srand(time(NULL));
	
	//互斥锁初始化
	pthread_mutex_init(&mutex, NULL);

	ret = pthread_create(&thread1, NULL, mythread1, NULL);
	if(ret!=0)
	{
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	ret = pthread_create(&thread2, NULL, mythread2, NULL);
	if(ret!=0)
	{
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	//等待线程结束
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	//释放互斥锁
	pthread_mutex_destroy(&mutex);
	return 0;
}
