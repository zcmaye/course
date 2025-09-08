#include "_threadpool.h"
#include "BlockingQueue.h"
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define DEFAULT_TIME 2 		//管理线程检测时间

/* 任务结构 */
typedef struct{
	void (*function)(void*);
	void* arg;
}task_t;

/* 线程池结构 */
typedef struct threadpool_t{
    pthread_mutex_t lock;              /* 用于锁住本结构体 */    
    pthread_cond_t cond;               /* 条件变量线程同步 */    

	pthread_t *workers_tid;				//存放线程池中每个线程的ID
	pthread_t manager_tid;				//管理线程ID
	BlockingQueue* task_queue;		//任务队列

	int min_thr_num;				//最小线程数
	int max_thr_num;				//最大线程数
	int alive_thr_num;				//存活线程数
	int busy_thr_num;				//繁忙线程数
	int wait_exit_thr_num;			//等待退出线程数

	bool shutdown;					//是否结束线程池标志
}treadpool_t;

static void *worker_thread(void *threadpool);
static void *manager_thread(void *threadpool);

//检查线程是否存活
static int is_thread_alive(pthread_t tid) {
	int kill_rc = pthread_kill(tid, 0);     //发0号信号，测试线程是否存活
	if (kill_rc == ESRCH) {
		return false;
	}
	return true;
}

//创建线程池
threadpool_t* threadpool_create(int min_threads, int max_threads, int queue_size)
{
	if (min_threads <= 0 || max_threads <= 0 || min_threads > max_threads || queue_size <= 0) {
		fprintf(stderr, "Invalid threadpool parameters\n");
		return NULL;
	}
	threadpool_t* pool = NULL;
	do{
		pool = (threadpool_t*)malloc(sizeof(threadpool_t));
		if (!pool) {
			fprintf(stderr, "Failed to allocate threadpool\n");
			break;
		}

		// 初始化线程池结构
		memset(pool, 0, sizeof(threadpool_t));

		pool->min_thr_num = min_threads;
		pool->max_thr_num = max_threads;
		pool->alive_thr_num= 0;
		pool->busy_thr_num= 0;
		pool->wait_exit_thr_num = 0;
		pool->shutdown = false;

		// 初始化锁和条件变量
		if (pthread_mutex_init(&pool->lock, NULL) != 0 ||
				pthread_cond_init(&pool->cond, NULL) != 0) {
			fprintf(stderr, "Failed to initialize mutex or condition variable\n");
			break;
		}

		// 创建任务队列
		pool->task_queue = bque_create(queue_size);
		if (!pool->task_queue) {
			fprintf(stderr, "Failed to create task queue\n");
			break;
		}

		// 创建最大线程数量线程ID数组
		pool->workers_tid = (pthread_t*)malloc(sizeof(pthread_t) * max_threads);
		if (!pool->workers_tid) {
			fprintf(stderr, "Failed to create worke thread array\n");
			break;
		}

		// 创建最小数量的工作线程
		for (int i = 0; i < min_threads; i++) {
			if (pthread_create(pool->workers_tid + i, NULL, worker_thread, pool) != 0) {
				fprintf(stderr, "Failed to create worker thread\n");
				break;
			}
			pool->alive_thr_num++;
		}

		// 创建管理线程（用于动态调整线程数量）
		if (pthread_create(&pool->manager_tid, NULL, manager_thread, pool) != 0) {
			fprintf(stderr, "Failed to create manager thread\n");
			break;
		}
		pthread_detach(pool->manager_tid);

		printf("Threadpool created with %d min threads, %d max threads, queue size %d\n",
				min_threads, max_threads, queue_size);
		return pool;
	}while(false);

	threadpool_destroy(pool);
	return NULL;
}

//销毁线程池
bool threadpool_destroy(threadpool_t* pool)
{
   if (!pool) return false;
    
    pthread_mutex_lock(&pool->lock);
    pool->shutdown = true;
    pthread_mutex_unlock(&pool->lock);
    
    // 唤醒所有等待的线程
    pthread_cond_broadcast(&pool->cond);
    
    // 等待所有工作线程退出
	if(pool->workers_tid){
		for(int i =0;i < pool->max_thr_num;i++) {
			if(pool->workers_tid[i] !=0) {
				pthread_join(pool->workers_tid[i], NULL);
			}
		}
		free(pool->workers_tid);
	}

	// 销毁任务队列
	if (pool->task_queue) {
		threadpool_clear(pool);	
		bque_destroy(pool->task_queue);
    }
    
    // 销毁锁和条件变量
    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->cond);
    
    free(pool);
    return true;}

//将一个任务添加到线程池中
bool threadpool_add_task(threadpool_t* pool,void (*function)(void*),void *arg)
{
	if (!pool || !function) return false;

	pthread_mutex_lock(&pool->lock);
	if (pool->shutdown) {
		pthread_mutex_unlock(&pool->lock);
		return false;
	}
	pthread_mutex_unlock(&pool->lock);

	// 创建任务
	task_t* task = malloc(sizeof(task_t));
	if(!task) {
		fprintf(stderr, "Failed to create task\n");
		return false;
	}
	task->function = function;
	task->arg = arg;

	// 添加到任务队列
	return bque_push(pool->task_queue,task);
}

//获取线程数
int threadpool_max_thread_num(threadpool_t* pool)
{
    if (!pool) return 0;
    pthread_mutex_lock(&pool->lock);
    int count = pool->alive_thr_num;
    pthread_mutex_unlock(&pool->lock);
    return count;
}

//获取繁忙线程数
int threadpool_busy_thread_num(threadpool_t* pool)
{
	if (!pool) return 0;
	pthread_mutex_lock(&pool->lock);
	int count = pool->busy_thr_num;
	pthread_mutex_unlock(&pool->lock);
	return count;
}

//获取正在等待的任务数
int threadpool_waiting_tasks(threadpool_t* pool)
{
    if (!pool) return 0;
    return bque_size(pool->task_queue);
}

//清空正在等待的任务
void threadpool_clear(threadpool_t* pool)
{
    if (!pool) return;
	if (pool->task_queue) {
		while(!bque_isEmpty(pool->task_queue)) {
			Data v;
			if(bque_pop_front(pool->task_queue,&v) && v) {
				free(v);
			}
		}
	}
}

//等待所有任务完成
void threadpool_wait(threadpool_t* pool)
{
    if (!pool) return;
    
    while (!bque_isEmpty(pool->task_queue) || pool->busy_thr_num> 0) {
        usleep(100000); // 100ms
    }
}

// 工作线程函数
static void* worker_thread(void* arg) {
    threadpool_t* pool = (threadpool_t*)arg;
    
    while (true) {
        pthread_mutex_lock(&pool->lock);
        
        // 检查是否需要退出
        while (bque_isEmpty(pool->task_queue) && !pool->shutdown) {
            printf("Thread workder wait \n");
            if (pool->wait_exit_thr_num > 0) {
                pool->wait_exit_thr_num--;
				
                if (pool->alive_thr_num > pool->min_thr_num) {
                    pool->alive_thr_num--;
					for(int i = 0;i<pool->max_thr_num;i++) {
						if(pool->workers_tid[i] == pthread_self()) {
							pool->workers_tid[i] = -1;
						}
					}
                    pthread_mutex_unlock(&pool->lock);
                    printf("Thread %lx exiting\n", (long)pthread_self());
                    return NULL;
                }
                pool->wait_exit_thr_num++; // 不能退出，恢复计数
            }
            //pthread_cond_wait(&pool->cond, &pool->lock);
			struct timespec ts;
			clock_gettime(CLOCK_REALTIME,&ts);
			ts.tv_sec+=1;
            pthread_cond_timedwait(&pool->cond, &pool->lock,&ts);
        }
		printf("Thread workder running \n");
        
        // 检查线程池状态
        if (pool->shutdown) {
            pool->alive_thr_num--;
            pthread_mutex_unlock(&pool->lock);
            printf("Thread %lx exiting due to shutdown\n", (long)pthread_self());
            return NULL;
        }
        
        pthread_mutex_unlock(&pool->lock);
        
        // 获取任务
        Data task_data;
        if (bque_pop_front(pool->task_queue, &task_data) && task_data) {
            task_t* task = (task_t*)task_data;
            
            // 执行任务
            pthread_mutex_lock(&pool->lock);
            pool->busy_thr_num++;
            pthread_mutex_unlock(&pool->lock);
            
            task->function(task->arg);
			free(task);
            
            pthread_mutex_lock(&pool->lock);
            pool->busy_thr_num--;
            pthread_mutex_unlock(&pool->lock);
        }
		usleep(10*1000);
    }
    
    return NULL;
}

// 管理线程函数（动态调整线程数量）
static void* manager_thread(void* arg) {
    threadpool_t* pool = (threadpool_t*)arg;

    while (!pool->shutdown) {
        sleep(DEFAULT_TIME); // 每2秒检查一次
        
        pthread_mutex_lock(&pool->lock);
        int queue_size = bque_size(pool->task_queue);
        int max_thr_num  = pool->max_thr_num;
        int min_thr_num  = pool->min_thr_num;
        int alive_thr_num = pool->alive_thr_num;
        int busy_thr_num = pool->busy_thr_num;
		pthread_mutex_unlock(&pool->lock);
        
        // 根据需要创建新线程
        if (queue_size > alive_thr_num && alive_thr_num < max_thr_num) {
			pthread_mutex_lock(&pool->lock);
            int add_count = 0;
            int max_add = max_thr_num - alive_thr_num;
            
			//查找空闲位置并创建线程
            for (int i = 0; i < max_thr_num && add_count < max_add; i++) {
				pthread_t* worker = pool->workers_tid + i;
				//线程存活往下找
				if(*worker == 0 || !is_thread_alive(pool->workers_tid[i])) {
					if(*worker > 0) {
						printf("Manager: wait thr\n");
						pthread_join(*worker,NULL);
					}
				}
                if (pthread_create(worker, NULL, worker_thread, pool) == 0) {
                    pool->alive_thr_num++;
                    add_count++;
                    printf("Manager: added new thread, total: %d\n", pool->alive_thr_num);
                } else {
                    break;
                }
            }
			pthread_mutex_unlock(&pool->lock);
        }
        
        // 根据需要销毁空闲线程
        if (busy_thr_num * 2 < alive_thr_num && alive_thr_num > min_thr_num) {
			pthread_mutex_lock(&pool->lock);
            pool->wait_exit_thr_num = 2; // 每次最多销毁2个线程
            pthread_cond_broadcast(&pool->cond);
			pthread_mutex_unlock(&pool->lock);
        }
        
		printf("Manager check finished\n");
    }
    
    return NULL;
}

