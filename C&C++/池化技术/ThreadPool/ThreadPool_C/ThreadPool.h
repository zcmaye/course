#ifndef THREADPOLL_H_
#define THREADPOLL_H_
#include <pthread.h>

#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>

typedef struct ThreadPool ThreadPool;
//创建线程池
ThreadPool* threadPoolCreate(int min,int max,int queSize);

//销毁线程池
bool threadPoolDestroy(ThreadPool* pool);

//添加任务
void threadPoolAdd(ThreadPool* pool, void(*fun)(void*),void*arg);

//获取正在工作的线程个数
int threadPoolBusyNum(ThreadPool* pool);

//获取存活的线程的个数
int threadPoolActiveNum(ThreadPool* pool);


#endif // !THREADPOLL_H_


