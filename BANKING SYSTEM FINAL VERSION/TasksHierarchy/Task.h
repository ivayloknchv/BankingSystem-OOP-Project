#pragma once
#include <fstream>
#include "../Helpers/MyString.h"
#include "../Helpers/HelperFuncs.h"

enum class TaskType
{
	Unknown,
	Open,
	Close,
	Change
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

	virtual void writeToFile(std::ofstream& ofs) const = 0;
	virtual void readFromFile(std::ifstream& ifs) = 0;
};

