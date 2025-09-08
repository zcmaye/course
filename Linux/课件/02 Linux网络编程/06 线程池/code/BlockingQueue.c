#include "BlockingQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct BlockingQueue{
	Data* data;			/*!数组指针*/
	int capacity;		/*!容量*/
	int front;			/*!队头指针*/	
	int rear;			/*!队尾指针*/

	pthread_mutex_t mutex;		/*!互斥锁*/
	pthread_cond_t not_empty;	/*!不为空条件变量*/
	pthread_cond_t not_full;	/*!不为满条件变量*/
};

BlockingQueue* bque_create(int capacity)
{
	BlockingQueue* que = malloc(sizeof(BlockingQueue));
	if(!que) {
		printf("blocking quque malloc error\n");
		return NULL;
	}
	if(bque_init(que,capacity)) {
		return que;
	}
	bque_destroy(que);
	return NULL;
}
bool bque_init(BlockingQueue* que,int capacity)
{
	if(!que || capacity <=0) {
		printf("quque ptr is null or capacity is zero!\n");
		return false;
	}
	capacity +=1;
	que->data = malloc(sizeof(Data) * capacity);
	if(!que->data) {
		printf("quque data alloc failed!\n");
		return false;
	}
	que->capacity = capacity;
	que->front = 0;
	que->rear = 0;

	pthread_mutex_init(&que->mutex,NULL);
	pthread_cond_init(&que->not_empty,NULL);
	pthread_cond_init(&que->not_full,NULL);

	return true;
}
//销毁队列
void bque_destroy(BlockingQueue* que)
{
	if(!que) {
		return;
	}

	pthread_mutex_destroy(&que->mutex);
	pthread_cond_destroy(&que->not_empty);
	pthread_cond_destroy(&que->not_full);

	if(que->data) {
		free(que->data);
	}
	que->front = 0;
	que->rear = 0;
	free(que);
}
//队列队列容量
int bque_capacity(BlockingQueue* que)
{
	return que->capacity - 1;
}
//队列元素数量
int bque_size(BlockingQueue* que)
{
	pthread_mutex_lock(&que->mutex);
	int size = (que->rear - que->front + que->capacity) % que->capacity;
	pthread_mutex_unlock(&que->mutex);
	return size;
}
//队列是否为空
bool bque_isEmpty(BlockingQueue*que)
{
	pthread_mutex_lock(&que->mutex);
	bool empty = que->front == que->rear;
	pthread_mutex_unlock(&que->mutex);
	return empty;
}
//队列是否已满
bool bque_isFull(BlockingQueue*que)
{
	pthread_mutex_lock(&que->mutex);
	bool full = (que->rear + 1) % que->capacity == que->front;
	pthread_mutex_unlock(&que->mutex);
	return full;
}
//入队
bool bque_push(BlockingQueue*que,Data value)
{
	pthread_mutex_lock(&que->mutex);
	//等待队列不满
	while((que->rear + 1) % que->capacity == que->front) {
		printf("bque push wait~\n");
		pthread_cond_wait(&que->not_full,&que->mutex);
	}

	que->data[que->rear] = value;
	que->rear = (que->rear + 1) % que->capacity;

	pthread_cond_signal(&que->not_empty);
	pthread_mutex_unlock(&que->mutex);
	return true;
}
//出队
bool bque_pop(BlockingQueue*que/*,Data* value*/)
{
	pthread_mutex_lock(&que->mutex);

	//等待队列非空
	while(que->front == que->rear) {
		pthread_cond_wait(&que->not_empty,&que->mutex);
	}
	
	//*value = que->data[que->front];
	que->front = (que->front + 1) % que->capacity;

	pthread_cond_signal(&que->not_full);
	pthread_mutex_unlock(&que->mutex);
	return true;
}
//出队并获取队头元素
bool bque_pop_front(BlockingQueue*que,Data*value)
{
	*value = NULL;
	pthread_mutex_lock(&que->mutex);

	//等待队列非空
	while(que->front == que->rear) {
		printf("bque pop front wait~\n");
		pthread_cond_wait(&que->not_empty,&que->mutex);
	}

	*value = que->data[que->front];
	que->front = (que->front + 1) % que->capacity;

	pthread_cond_signal(&que->not_full);
	pthread_mutex_unlock(&que->mutex);
	return true;

}
//队头元素
Data* bque_front(BlockingQueue*que)
{
	pthread_mutex_lock(&que->mutex);
	if(que->front == que->rear) {
		printf("que is empty,can't front!\n");
		pthread_mutex_unlock(&que->mutex);
		return NULL;
	}
	Data* result = &que->data[que->front];
	pthread_mutex_unlock(&que->mutex);
	return result;
}

