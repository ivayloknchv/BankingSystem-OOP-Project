#include "Task.h"
#include <utility>

Task::Task(TaskType type) : _type(type)
{
}


TaskType Task::getType() const
{
	return _type;
}