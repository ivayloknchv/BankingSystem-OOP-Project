#pragma once
#include "Task.h"

class DataPlaceholderTask : public Task
{
protected:

	MyString _firstName = "Unknown";
	MyString _lastName = "Unknown";
	MyString _EGN = "Unknown";
	unsigned _age = 0;

public:

	DataPlaceholderTask(TaskType type);
	DataPlaceholderTask(TaskType type, const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age);
	DataPlaceholderTask(TaskType type, MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age);

	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getEGN() const;
	unsigned getAge() const;

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

