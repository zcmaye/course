#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_
#include <mutex>
#include <functional>
#include <queue>

//任务结构
class Task
{
public:
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
	template<typename Func, typename ...Args>
	void addTask(Func func, Args...args);

	Task takeTask();
	std::size_t size() { return _taskQue.size(); }
private:
	std::queue<Task> _taskQue;
	std::mutex _mutex;
};
template<typename Func, typename ...Args>
void TaskQueue::addTask(Func func, Args...args)
{
	addTask(Task(func, std::forward<Args>(args)...));
}
#endif // !TASKQUEUE_H_


