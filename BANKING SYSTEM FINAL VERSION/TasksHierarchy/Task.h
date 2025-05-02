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

protected:

	MyString _firstName = "Unknown";
	MyString _lastName = "Unknown";
	MyString _EGN = "Unknown";
	unsigned _age = 0;

public:

	Task() = default;
	Task(TaskType type);
	Task(TaskType type, const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age);
	Task(TaskType type, MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age);

	TaskType getType() const;
	
	virtual void viewTask() const = 0;
	virtual void getTaskPreview() const = 0;

	virtual Task* clone() const = 0;
	virtual ~Task() = default;

	virtual void approve() const = 0;
	virtual void disapprove() const = 0;

	virtual void writeToFile(std::ofstream& ofs) const = 0;
	virtual void readFromFile(std::ifstream& ifs) = 0;
};

