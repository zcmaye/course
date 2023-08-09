//线程退出函数测试
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

struct Test
{
	int data;
	char name[64];
};
int g_var = 9;
struct Test t;

//线程执行函数
void *mythread(void *arg)
{
	printf("child thread, pid==[%d], id==[%ld]\n", getpid(), pthread_self());
	//printf("[%p]\n", &g_var);
	//pthread_exit(&g_var);
	memset(&t, 0x00, sizeof(t));
	t.data = 99;
	strcpy(t.name, "xiaowen");
	pthread_exit(&t);
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

	//回收子线程
	void *p = NULL;
	pthread_join(thread, &p);	
	//int n = *(int *)p;
	struct Test *pt = (struct Test *)p;
	printf("child exit status:[%d],[%s],[%p]\n",  pt->data, pt->name, p);

	return 0;
}
