//使用信号量实现生产者和消费者模型
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
typedef struct node
{
	int data;
	struct node *next;
}NODE;

NODE *head = NULL;

//定义信号量
sem_t sem_producer;
sem_t sem_consumer;

//生产者线程
void *producer(void *arg)
{
	NODE *pNode = NULL;
	while(1)
	{
		//生产一个节点
		pNode = (NODE *)malloc(sizeof(NODE));
		if(pNode==NULL)
		{
			perror("malloc error");
			exit(-1);
		}
		pNode->data = rand()%1000;
		printf("P:[%d]\n", pNode->data);

		//加锁
		sem_wait(&sem_producer); //--

		pNode->next = head;
		head = pNode;

		//解锁
		sem_post(&sem_consumer);  //相当于++

		sleep(rand()%3);
	}
}


//消费者线程
void *consumer(void *arg)
{
	NODE *pNode = NULL;
	while(1)
	{
		//加锁
		sem_wait(&sem_consumer); //相当于--
		
		printf("C:[%d]\n", head->data);	
		pNode = head;
		head = head->next;

		//解锁
		sem_post(&sem_producer); //相当于++

		free(pNode);
		pNode = NULL;

		sleep(rand()%3);
	}
}

int main()
{
	int ret;
	pthread_t thread1;
	pthread_t thread2;

	//初始化信号量
	sem_init(&sem_producer, 0, 5);
	sem_init(&sem_consumer, 0, 0);

	//创建生产者线程
	ret = pthread_create(&thread1, NULL, producer, NULL);
	if(ret!=0)
	{
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	//创建消费者线程
	ret = pthread_create(&thread2, NULL, consumer, NULL);
	if(ret!=0)
	{
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	//等待线程结束
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	//释放信号量资源
	sem_destroy(&sem_producer);
	sem_destroy(&sem_consumer);

	return 0;
}
