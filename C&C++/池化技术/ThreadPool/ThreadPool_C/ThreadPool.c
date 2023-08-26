#include "ThreadPool.h"

//任务结构
typedef struct Task
{
	void (*function)(void* arg);	//任务函数
	void* arg;						//参数
}Task;


//线程池结构
struct ThreadPool
{
	//任务队列
	Task* tasksQue;
	int queCapacity;
	int queSize;
	int queFront;	//队头
	int queRear;	//队尾

	pthread_t managerID;	//管理线程ID
	pthread_t* threadIDs;	//工作线程ID
	int minNum;				//最小线程数
	int maxNum;				//最大线程数
	int busyNum;			//正在工作的线程数（忙的）
	int activeNum;			//活动的线程数
	int exitNum;			//要销毁的线程个数
	pthread_mutex_t mutexpool;	//锁整个线程池
	pthread_mutex_t mutexBusy;	//锁busyNum变量
	pthread_cond_t	notFull;	//任务队列是不是满了
	pthread_cond_t	notEmpty;	//任务队列是不是空了

	bool shutdown;				//是否销毁线程池
};
//内部函数
void* worker(void* arg);
void* manager(void* arg);
void threadExit(ThreadPool* pool);
//公有函数
ThreadPool* threadPoolCreate(int min, int max, int queSize)
{
	ThreadPool* pool = calloc(1, sizeof(ThreadPool));
	if (!pool)
	{
		printf("calloc threadpool create failed!\n");
		return NULL;
	}

	pool->threadIDs = calloc(max, sizeof(pthread_t));
	if (!pool->threadIDs)
	{
		printf("calloc pool->threadIDs create failed!\n");
		free(pool);
		return NULL;
	}
	pool->minNum = min;
	pool->maxNum = max;
	pool->busyNum = 0;
	pool->activeNum = min;
	pool->exitNum = 0;


	if (pthread_mutex_init(&pool->mutexpool, NULL) != 0 ||
		pthread_mutex_init(&pool->mutexBusy,NULL)!=0 ||
		pthread_cond_init(&pool->notFull,NULL)!=0 ||
		pthread_cond_init(&pool->notEmpty,NULL)!=0
		)
	{
		printf("mutex or condition init failed!\n");
		free(pool);
		free(pool->threadIDs);
		return NULL;
	}

	//任务队列
	pool->tasksQue = calloc(queSize, sizeof(Task));
	pool->queCapacity = queSize;

	pool->shutdown = false;

	//创建线程
	pthread_create(&pool->managerID, NULL, manager, pool);
	for (int i = 0; i < pool->minNum; i++)
	{
		pthread_create(&pool->threadIDs[i], NULL, worker, pool);
	}

	return pool;
}

bool threadPoolDestroy(ThreadPool* pool)
{
	if (!pool)
	{
		return false;
	}
	//关闭线程池
	pool->shutdown = true;
	//阻塞回收管理者线程
	pthread_join(pool->managerID, NULL);
	//唤醒阻塞的消费者线程
	for (int i = 0; i < pool->activeNum; i++)
	{
		pthread_cond_signal(&pool->notEmpty);
	}

	pthread_mutex_destroy(&pool->mutexBusy);
	pthread_mutex_destroy(&pool->mutexpool);
	pthread_cond_destroy(&pool->notEmpty);
	pthread_cond_destroy(&pool->notFull);
	//释放堆内存
	free(pool->tasksQue);
	free(pool->threadIDs);
	free(pool);


	return false;
}

void threadPoolAdd(ThreadPool* pool, void(*fun)(void*), void* arg)
{
	pthread_mutex_lock(&pool->mutexpool);
	while (pool->queSize == pool->queCapacity && !pool->shutdown)
	{
		//阻塞生产者线程
		pthread_cond_wait(&pool->notFull, &pool->mutexpool);
	}
	if (pool->shutdown)
	{
		pthread_mutex_unlock(&pool->mutexpool);
		return;
	}
	//添加任务
	pool->tasksQue[pool->queRear] = (Task){fun,arg };
	pool->queRear = (pool->queRear + 1) % pool->queCapacity;
	pool->queSize++;

	pthread_cond_signal(&pool->notEmpty);

	pthread_mutex_unlock(&pool->mutexpool);
}

int threadPoolBusyNum(ThreadPool* pool)
{
	pthread_mutex_lock(&pool->mutexpool);
	int busyNum = pool->busyNum;
	pthread_mutex_unlock(&pool->mutexpool);
	return busyNum;
}

int threadPoolActiveNum(ThreadPool* pool)
{
	pthread_mutex_lock(&pool->mutexpool);
	int activeNum = pool->activeNum;
	pthread_mutex_unlock(&pool->mutexpool);
	return activeNum;
}

void* worker(void* arg)
{
	ThreadPool* pool = (ThreadPool*)arg;

	while (true)
	{
		//加锁
		pthread_mutex_lock(&pool->mutexpool);
		//当前任务队列是否为空
		while (pool->queSize == 0 && !pool->shutdown)
		{
			//阻塞工作线程，等任务
			pthread_cond_wait(&pool->notEmpty, &pool->mutexpool);
		
			//判断是不是要销毁线程
			if (pool->exitNum > 0)
			{
				--pool->exitNum;
				if (pool->activeNum > pool->minNum)
				{
					--pool->activeNum;
					pthread_mutex_unlock(&pool->mutexpool);
					threadExit(pool);
				}

			}
		}

		//判断线程池是否被关闭了
		if (pool->shutdown)
		{
			pthread_mutex_unlock(&pool->mutexpool);
			pthread_exit(NULL);
			break;
		}

		//从任务队列取出一个任务
		Task task = pool->tasksQue[pool->queFront];
		//移动头结点
		pool->queFront = (pool->queFront + 1) % pool->queCapacity;
		--pool->queSize;
		//解锁
		pthread_cond_signal(&pool->notFull);
		pthread_mutex_unlock(&pool->mutexpool);

		//开始任务
		printf("thread %ld start wroking...\n",pthread_self());
		pthread_mutex_lock(&pool->mutexBusy);
		++pool->busyNum;
		pthread_mutex_unlock(&pool->mutexBusy);

		task.function(task.arg);
		free(task.arg); 

		printf("thread %ld end wroking...\n", pthread_self());
		pthread_mutex_lock(&pool->mutexBusy);
		--pool->busyNum;
		pthread_mutex_unlock(&pool->mutexBusy);
	}

	return NULL;
}

void* manager(void* arg)
{
	ThreadPool* pool = (ThreadPool*)arg;

	while (!pool->shutdown)
	{
		//每隔三秒检测一次
		sleep(3);

		//取出线程池中任务的数量和当前线程数量
		pthread_mutex_lock(&pool->mutexpool);
		int queSize = pool->queSize;
		int activeNum = pool->activeNum;
		pthread_mutex_unlock(&pool->mutexpool);

		//取出忙线程数量
		pthread_mutex_lock(&pool->mutexBusy);
		int busyNum = pool->busyNum;
		pthread_mutex_unlock(&pool->mutexBusy);

		//添加线程
		//任务个数 > 存活的线程个数 && 存活的线程数 < 最大线程数
		if (queSize > activeNum && activeNum < pool->maxNum)
		{
			pthread_mutex_lock(&pool->mutexpool);
			int counter = 0;
			for (int i = 0; i < pool->maxNum && pool->activeNum < pool->maxNum && counter < 2; ++i)
			{
				if (pool->threadIDs[i] == 0)
				{
					pthread_create(&pool->threadIDs[i], NULL, worker, pool);
					++counter;
					++pool->activeNum;
				}
			}
			pthread_mutex_unlock(&pool->mutexpool);

		}
		//销毁线程
		//忙线程 * 2  < 存活的线程数 && 存活的线程 > 最小线程数
		if (busyNum * 2 < activeNum && activeNum > pool->minNum)
		{
			pthread_mutex_lock(&pool->mutexpool);
			pool->exitNum = 2;
			pthread_mutex_unlock(&pool->mutexpool);
			//让工作线程自杀
			for (int i = 0; i < 2; i++)
			{
				pthread_cond_signal(&pool->notEmpty);
				
			}
		}
	}
	return NULL;
}

void threadExit(ThreadPool* pool)
{
	pthread_t tid = pthread_self();
	for (int i = 0; i < pool->maxNum; i++)
	{
		if (pool->threadIDs[i] == tid)
		{
			pool->threadIDs[i] = 0;
			printf("threadExit called,%ld exiting...!\n",tid);
			break;
		}
	}
	pthread_exit(NULL);
}
