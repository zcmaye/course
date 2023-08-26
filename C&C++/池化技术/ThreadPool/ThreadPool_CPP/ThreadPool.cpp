#include "ThreadPool.h"
#include <algorithm>
ThreadPool::ThreadPool(int minThreadCount, int maxThreadCount)
{
	_taskQue = new TaskQueue;

	_threadIDs.resize(maxThreadCount);
	_minThreadCount		= minThreadCount;
	_maxThreadCount		= maxThreadCount;
	_busyThreadCount	= 0;
	_activeThreadCount	= minThreadCount;
	_exitThreadCount	= 0;


	if (pthread_mutex_init(&_mutexpool, NULL) != 0 ||
		pthread_cond_init(&_notEmpty, NULL) != 0
		)
	{
		printf("mutex or condition init failed!\n");
	}

	//任务队列
	_shutdown = false;

	//创建线程
	pthread_create(&_managerID, NULL, manager,this);
	for (int i = 0; i < _minThreadCount; i++)
	{
		pthread_create(&_threadIDs[i], NULL, worker,this);
	}
}

ThreadPool::~ThreadPool()
{
	//关闭线程池
	_shutdown = true;
	//阻塞回收管理者线程
	pthread_join(_managerID, nullptr);
	//唤醒阻塞的消费者线程
	//for (int i = 0; i < _activeThreadCount; i++)
	//{
	//	pthread_cond_signal(&_notEmpty);
	//}
	pthread_cond_broadcast(&_notEmpty);

	delete _taskQue;
	pthread_mutex_destroy(&_mutexpool);
	pthread_cond_destroy(&_notEmpty);
	printf("%s\n", __FUNCTION__);
}

void ThreadPool::addTask(void(*fun)(void*), void* arg)
{
	addTask(Task(fun, arg));
}

void ThreadPool::addTask(const Task& task)
{
	if (_shutdown)
	{
		return;
	}
	_taskQue->addTask(task);
	pthread_cond_signal(&_notEmpty);
}

int ThreadPool::busyThreadCount()
{
	int count = 0;
	pthread_mutex_lock(&_mutexpool);
	count = _busyThreadCount;
	pthread_mutex_unlock(&_mutexpool);
    return count;
}

int ThreadPool::activeThreadCount()
{
	int count = 0;
	pthread_mutex_lock(&_mutexpool);
	count = _activeThreadCount;
	pthread_mutex_unlock(&_mutexpool);
	return count;
}

void* ThreadPool::manager(void* arg)
{
	ThreadPool* pool = static_cast<ThreadPool*>(arg);
	while (!pool->_shutdown)
	{
		//每隔三秒检测一次
		sleep(3);

		//取出线程池中任务的数量和当前线程数量
		pthread_mutex_lock(&pool->_mutexpool);
		int queSize = (int)pool->_taskQue->size();
		int activeThreadCount = pool->_activeThreadCount;
		//取出忙线程数量
		int busyThreadCount = pool->_busyThreadCount;
		pthread_mutex_unlock(&pool->_mutexpool);

		//添加线程
		//任务个数 > 存活的线程个数 && 存活的线程数 < 最大线程数
		if (queSize > activeThreadCount && activeThreadCount < pool->_maxThreadCount)
		{
			pthread_mutex_lock(&pool->_mutexpool);
			int counter = 0;
			for (int i = 0; i < pool->_maxThreadCount && pool->_activeThreadCount < pool->_maxThreadCount && counter < 2; ++i)
			{
				if (pool->_threadIDs[i] == 0)
				{
					pthread_create(&pool->_threadIDs[i], NULL, worker, pool);
					++counter;
					++pool->_activeThreadCount;
				}
			}
			pthread_mutex_unlock(&pool->_mutexpool);

		}
		//销毁线程
		//忙线程 * 2  < 存活的线程数 && 存活的线程 > 最小线程数
		if (busyThreadCount * 2 < activeThreadCount && activeThreadCount > pool->_minThreadCount)
		{
			pthread_mutex_lock(&pool->_mutexpool);
			pool->_exitThreadCount = 2;
			pthread_mutex_unlock(&pool->_mutexpool);
			//让工作线程自杀
			for (int i = 0; i < 2; i++)
			{
				pthread_cond_signal(&pool->_notEmpty);

			}
		}
	}
	return nullptr;
}

void* ThreadPool::worker(void* arg)
{
	ThreadPool* pool = static_cast<ThreadPool*>(arg);
	while (true)
	{
		//加锁
		pthread_mutex_lock(&pool->_mutexpool);
		//当前任务队列是否为空
		while (pool->_taskQue->size() == 0 && !pool->_shutdown)
		{
			//阻塞工作线程，等任务
			pthread_cond_wait(&pool->_notEmpty, &pool->_mutexpool);

			//判断是不是要销毁线程
			if (pool->_exitThreadCount > 0)
			{
				--pool->_exitThreadCount;
				if (pool->_activeThreadCount > pool->_minThreadCount)
				{
					--pool->_activeThreadCount;
					pthread_mutex_unlock(&pool->_mutexpool);
					pool->threadExit();
				}

			}
		}

		//判断线程池是否被关闭了
		if (pool->_shutdown)
		{
			pthread_mutex_unlock(&pool->_mutexpool);
			pthread_exit(NULL);
			break;
		}

		//从任务队列取出一个任务
		Task task = pool->_taskQue->takeTask();
		//解锁
		//pthread_cond_signal(&pool->_notFull);
		pthread_mutex_unlock(&pool->_mutexpool);

		//开始任务
		printf("thread %#X start wroking...\n", pthread_self());
		pthread_mutex_lock(&pool->_mutexpool);
		++pool->_busyThreadCount;
		pthread_mutex_unlock(&pool->_mutexpool);

		task();

		printf("thread %#X end wroking...\n", pthread_self());
		pthread_mutex_lock(&pool->_mutexpool);
		--pool->_busyThreadCount;
		pthread_mutex_unlock(&pool->_mutexpool);
	}
	return nullptr;
}

void ThreadPool::threadExit()
{
	pthread_t tid = pthread_self();
	auto it = std::find(_threadIDs.begin(), _threadIDs.end(), tid);
	if (it != _threadIDs.end())
	{
		*it = 0;
		printf("threadExit called,%#X exiting...!\n", tid);
		printf("thread Count .................. %d  %d\n",_busyThreadCount,_activeThreadCount);
	}
	pthread_exit(NULL);
}
