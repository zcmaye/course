#include<stdio.h>
#include"ThreadPool.h"
#include<malloc.h>

void taskFunc(void* arg)
{
	int num = *(int*)arg;
	printf("thread is working,number is %d,id is %ld\n", num, pthread_self());
	sleep(1);
}

int main()
{
	ThreadPool* pool = threadPoolCreate(3, 10, 10);

	for (int i = 0; i < 100; i++)
	{
		int* num = calloc(1, sizeof(int));
		*num = i + 100;
		threadPoolAdd(pool,taskFunc, num);
	}

	sleep(30);
	threadPoolDestroy(pool);

	return 0;
}
