#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_

#include <pthread.h>

#include <unistd.h>
#include <functional>
#include <queue>

//任务结构
class Task
{
public:
	using CallBack = void (*)(void*);
public:
	Task() {}
	template<typename Func,typename ...Args>
	Task(Func func, Args...args)
	{
		//把任何函数都绑定成void(void)形式的
		_function = std::bind(func, std::forward<Args>(args)...);
	}
	~Task() { }
	void operator()() { if (_function)_function(); }
	bool empty() { return !_function; }
private:
	std::function<void()> _function;	
};

class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();
	void addTask(const Task& task);
	void addTask(Task::CallBack func, void* arg);
	Task takeTask();
	std::size_t size() { return _taskQue.size(); }
private:
	std::queue<Task> _taskQue;
	pthread_mutex_t _mutex;
};
#endif // !TASKQUEUE_H_


