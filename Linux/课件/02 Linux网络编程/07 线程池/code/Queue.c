#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue{
	Data* data;			/*!数组指针*/
	int capacity;		/*!容量*/
	int front;			/*!队头指针*/	
	int rear;			/*!队尾指针*/
} Queue;

Queue* que_create(int capacity)
{
	Queue* que = malloc(sizeof(Queue));
	if(!que) {
		printf("quque malloc error\n");
		return NULL;
	}
	if(que_init(que,capacity)) {
		return que;
	}
	que_destroy(que);
	return NULL;
}

bool que_init(Queue* que,int capacity)
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

	return true;
}
//销毁队列
void que_destroy(Queue* que)
{
	if(!que) {
		return;
	}
	if(que->data) {
		free(que->data);
	}
	que->front = 0;
	que->rear = 0;
	free(que);
}
//队列队列容量
int que_capacity(Queue* que)
{
	return que->capacity - 1;
}
//队列元素数量
int que_size(Queue* que)
{
	return (que->rear - que->front + que->capacity) % que->capacity;
}
//队列是否为空
bool que_isEmpty(Queue*que)
{
	return que->front == que->rear;
}
//队列是否已满
bool que_isFull(Queue*que)
{
	return (que->rear + 1) % que->capacity == que->front;
}
//入队
bool que_push(Queue*que,Data value)
{
	if(que_isFull(que)) {
		printf("que is full,can't push!\n");
		return false;
	}

	que->data[que->rear] = value;
	que->rear = (que->rear + 1) % que->capacity;
	return true;
}
//出队
bool que_pop(Queue*que)
{
	if(que_isEmpty(que)) {
		printf("que is empty,can't pop!\n");
		return false;
	}
	que->front = (que->front + 1) % que->capacity;
	return true;
}
//队头元素
Data* que_front(Queue*que)
{
	if(que_isEmpty(que)) {
		printf("que is empty,can't front!\n");
		return NULL;
	}
	return &que->data[que->front];
}

