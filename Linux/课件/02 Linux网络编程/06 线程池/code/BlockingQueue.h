#pragma once
#include <stdbool.h>

typedef void* Data;

typedef struct BlockingQueue BlockingQueue;

//创建队列
BlockingQueue* bque_create(int capacity);
//初始化队列
bool bque_init(BlockingQueue* que,int capacity);
//销毁队列
void bque_destroy(BlockingQueue* que);
//队列队列容量
int bque_capacity(BlockingQueue* que);
//队列元素数量
int bque_size(BlockingQueue* que);
//队列是否为空
bool bque_isEmpty(BlockingQueue*que);
//队列是否已满
bool bque_isFull(BlockingQueue*que);
//入队
bool bque_push(BlockingQueue*que,Data value);
//出队
bool bque_pop(BlockingQueue*que);
//出队并获取队头元素
bool bque_pop_front(BlockingQueue*que,Data*value);
//队头元素
Data* bque_front(BlockingQueue*que);
