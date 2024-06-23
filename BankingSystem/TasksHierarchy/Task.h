#pragma once
#include "MyString.h"

enum class TaskType
{
	Unknown,
	Open,
	Close,
	Change,
	Validate
};

class Task
{
private:

	TaskType _type = TaskType::Unknown;

public:

	Task() = default;
	Task(TaskType type);
	TaskType getType() const;
	
	virtual void viewTask() const = 0;
	virtual void getTaskPreview() const = 0;

	virtual Task* clone() const = 0;
	virtual ~Task() = default;
};

