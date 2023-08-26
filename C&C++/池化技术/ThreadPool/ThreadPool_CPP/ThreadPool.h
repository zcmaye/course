#ifndef THREADPOOL_H_
#define THREADPOOL_H_
#include"TaskQueue.h"
class ThreadPool
{
public:
	ThreadPool(int minThreadCount,int maxThreadCount);
	~ThreadPool();

	//添加任务
	void addTask(void(*fun)(void*), void* arg);
	void addTask(const Task& task);

	//获取正在工作的线程个数
	int busyThreadCount();

	//获取存活的线程的个数
	int activeThreadCount();
private:
	static void* manager(void* arg);
	static void* worker(void* arg);
	void threadExit();
private:
	TaskQueue* _taskQue;		//多个线程共享，必须new

	pthread_t _managerID;	//管理线程ID
	std::vector<pthread_t> _threadIDs;	//工作线程ID
	int _minThreadCount;				//最小线程数
	int _maxThreadCount;				//最大线程数
	int _busyThreadCount;			//正在工作的线程数（忙的）
	int _activeThreadCount;			//活动的线程数
	int _exitThreadCount;			//要销毁的线程个数
	pthread_mutex_t _mutexpool;	//锁整个线程池
	pthread_cond_t	_notEmpty;	//任务队列是不是空了

	bool _shutdown;				//是否销毁线程池
};

#endif // !THREADPOOL_H_



