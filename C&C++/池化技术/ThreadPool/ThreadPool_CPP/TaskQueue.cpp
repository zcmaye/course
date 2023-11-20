#include "TaskQueue.h"

TaskQueue::TaskQueue()
{
	pthread_mutex_init(&_mutex,nullptr);
}

TaskQueue::~TaskQueue()
{
	pthread_mutex_destroy(&_mutex);
}

void TaskQueue::addTask(const Task& task)
{
	pthread_mutex_lock(&_mutex);
	_taskQue.push(task);
	pthread_mutex_unlock(&_mutex);
}

void TaskQueue::addTask(Task::CallBack func, void* arg)
{
	addTask(Task(func, arg));
}

Task TaskQueue::takeTask()
{
	Task task;
	pthread_mutex_lock(&_mutex);
	if (!_taskQue.empty())
	{
		task = _taskQue.front();
		_taskQue.pop();
	}
	pthread_mutex_unlock(&_mutex);
	return task;
}
