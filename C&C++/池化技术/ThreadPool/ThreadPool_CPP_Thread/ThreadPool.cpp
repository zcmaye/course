#include "ThreadPool.h"
#include <algorithm>

ThreadPool::ThreadPool(int minThreadCount, int maxThreadCount)
{
	_taskQue = new TaskQueue;

	_workerThreads.resize(maxThreadCount);
	_minThreadCount		= minThreadCount;
	_maxThreadCount		= maxThreadCount;
	_busyThreadCount	= 0;
	_activeThreadCount	= minThreadCount;
	_exitThreadCount	= 0;


	//任务队列
	_shutdown = false;

	//创建线程
	_managerThread = std::thread(manager, this);
	for (int i = 0; i < _minThreadCount; i++)
	{
		_workerThreads[i] = new std::thread(worker, this);
	}
}

ThreadPool::~ThreadPool()
{
	//关闭线程池
	_shutdown = true;
	//阻塞回收管理者线程
	if(_managerThread.joinable())
		_managerThread.join();
	//唤醒阻塞的消费者线程
	_notEmpty.notify_all();

	delete _taskQue;

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
	_notEmpty.notify_one();
}

int ThreadPool::busyThreadCount()
{
	int count = 0;
	std::lock_guard<std::mutex> lk(_mutexpool);
	count = _busyThreadCount;
    return count;
}

int ThreadPool::activeThreadCount()
{
	int count = 0;
	std::lock_guard<std::mutex> lk(_mutexpool);
	count = _activeThreadCount;
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
		pool->_mutexpool.lock();
		int queSize = (int)pool->_taskQue->size();
		int activeThreadCount = pool->_activeThreadCount;
		//取出忙线程数量
		int busyThreadCount = pool->_busyThreadCount;
		pool->_mutexpool.unlock();

		//添加线程
		//任务个数 > 存活的线程个数 && 存活的线程数 < 最大线程数
		if (queSize > activeThreadCount && activeThreadCount < pool->_maxThreadCount)
		{
			std::lock_guard<std::mutex> lk(pool->_mutexpool);
			int counter = 0;
			for (int i = 0; i < pool->_maxThreadCount && pool->_activeThreadCount < pool->_maxThreadCount && counter < 2; ++i)
			{
				if (pool->_workerThreads[i] == nullptr)
				{
					pool->_workerThreads[i] = new std::thread(worker, pool);
					++counter;
					++pool->_activeThreadCount;
				}
			}

		}
		//销毁线程
		//忙线程 * 2  < 存活的线程数 && 存活的线程 > 最小线程数
		if (busyThreadCount * 2 < activeThreadCount && activeThreadCount > pool->_minThreadCount)
		{
			pool->_mutexpool.lock();
			pool->_exitThreadCount = 2;
			pool->_mutexpool.unlock();

			//让工作线程自杀
			for (int i = 0; i < 2; i++)
			{
				pool->_notEmpty.notify_one();
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
		std::unique_lock<std::mutex>  ulk(pool->_mutexpool);
		ulk.lock();
		//当前任务队列是否为空
		while (pool->_taskQue->size() == 0 && !pool->_shutdown)
		{
			//阻塞工作线程，等任务
			pool->_notEmpty.wait(ulk);

			//判断是不是要销毁线程
			if (pool->_exitThreadCount > 0)
			{
				--pool->_exitThreadCount;
				if (pool->_activeThreadCount > pool->_minThreadCount)
				{
					--pool->_activeThreadCount;
					ulk.unlock();
					pool->threadExit();
				}

			}

		}

		//判断线程池是否被关闭了
		if (pool->_shutdown)
		{
			ulk.unlock();
			pool->threadExit();
			break;	//退出线程循环
		}

		//从任务队列取出一个任务
		Task task = pool->_taskQue->takeTask();
		//解锁
		//pthread_cond_signal(&pool->_notFull);
		ulk.unlock();

		//开始任务
		printf("thread %#X start wroking...\n", pthread_self());
		ulk.lock();
		++pool->_busyThreadCount;
		ulk.unlock();

		task();

		printf("thread %#X end wroking...\n", pthread_self());
		ulk.lock();
		--pool->_busyThreadCount;
		ulk.unlock();
	}
	return nullptr;
}

void ThreadPool::threadExit()
{
	auto tid = std::this_thread::get_id();
	auto it = std::find_if(_workerThreads.begin(), _workerThreads.end(), [=](std::thread* thr)
		{
			return thr->get_id() == tid;
		});
	if (it != _workerThreads.end())
	{
		delete *it;
		*it = nullptr;
		printf("threadExit called,%#X exiting...!\n", tid);
		printf("thread Count .................. %d  %d\n",_busyThreadCount,_activeThreadCount);
	}
}
