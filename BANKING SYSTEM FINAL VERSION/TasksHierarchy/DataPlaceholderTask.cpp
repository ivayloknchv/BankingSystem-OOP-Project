#include "DataPlaceholderTask.h"

DataPlaceholderTask::DataPlaceholderTask(TaskType type) : Task(type)
{
}

DataPlaceholderTask::DataPlaceholderTask(TaskType type, const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age)
	:Task(type), _firstName(firstName), _lastName(lastName), _EGN(EGN), _age(age)
{}

DataPlaceholderTask::DataPlaceholderTask(TaskType type, MyString && firstName, MyString && lastName, MyString && EGN, unsigned age)
	:Task(type), _firstName(std::move(firstName)), _lastName(std::move(lastName)), _EGN(std::move(EGN)), _age(age)
{}

const MyString& DataPlaceholderTask::getFirstName() const
{
	return _firstName;
}

const MyString& DataPlaceholderTask::getLastName() const
{
	return _lastName;
}

const MyString& DataPlaceholderTask::getEGN() const
{
	return _EGN;
}

unsigned DataPlaceholderTask::getAge() const
{
	return _age;
}

void DataPlaceholderTask::writeToFile(std::ofstream& ofs) const
{
	Task::writeToFile(ofs);
	writeStringToFile(ofs,_firstName);
	writeStringToFile(ofs,_lastName);
	writeStringToFile(ofs, _EGN);
	ofs.write((const char*)&_age, sizeof(unsigned));
}

void DataPlaceholderTask::readFromFile(std::ifstream& ifs)
{
	_firstName = readStringFromFile(ifs);
	_lastName = readStringFromFile(ifs);
	_EGN = readStringFromFile(ifs);
	ifs.read((char*)&_age, sizeof(unsigned));
}

