#include "TaskQueue.h"

TaskQueue::TaskQueue()
{
	
}

TaskQueue::~TaskQueue()
{
	
}

void TaskQueue::addTask(const Task& task)
{
	std::lock_guard<std::mutex> lk(_mutex);
	_taskQue.push(task);
}


Task TaskQueue::takeTask()
{
	Task task;
	std::lock_guard<std::mutex> lk(_mutex);
	if (!_taskQue.empty())
	{
		task = _taskQue.front();
		_taskQue.pop();
	}
	return task;
}
