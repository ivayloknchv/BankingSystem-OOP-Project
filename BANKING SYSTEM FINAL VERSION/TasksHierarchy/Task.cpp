#include "Task.h"
#include <utility>

Task::Task(TaskType type) : _type(type)
{
}


TaskType Task::getType() const
{
	return _type;
}

void Task::writeToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&_type, sizeof(TaskType));
}

