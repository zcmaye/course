#pragma once
#include <stdbool.h>

typedef struct threadpool_t threadpool_t;

//创建线程池
threadpool_t* threadpool_create(int min_threads, int max_threads, int queue_size);

//销毁线程池
bool threadpool_destroy(threadpool_t* pool); 

//将一个任务添加到线程池中
bool threadpool_add_task(threadpool_t* pool,void (*function)(void*),void *arg);

//获取线程数
int threadpool_max_thread_num(threadpool_t* pool);

//获取繁忙线程数
int threadpool_busy_thread_num(threadpool_t* pool);

//获取正在等待的任务数
int threadpool_waiting_tasks(threadpool_t* pool);

//清空正在等待的任务
void threadpool_clear(threadpool_t* pool);

//等待所有任务完成
void threadpool_wait(threadpool_t* pool);
