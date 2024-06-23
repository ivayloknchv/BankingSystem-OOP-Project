#include "OpenAccountTask.h"
#include <utility>
#include <iostream>

OpenAccountTask::OpenAccountTask() : DataPlaceholderTask(TaskType::Open)
{
}

OpenAccountTask::OpenAccountTask(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age):
	DataPlaceholderTask(TaskType::Open, firstName, lastName, EGN, age)
{}

OpenAccountTask::OpenAccountTask(MyString && firstName, MyString && lastName, MyString && EGN, unsigned age):
	DataPlaceholderTask(TaskType::Open, std::move(firstName), std::move(lastName), std::move(EGN), age)
{}

Task* OpenAccountTask::clone() const
{
	return new OpenAccountTask(*this);
}

void OpenAccountTask::viewTask() const
{
	std::cout << "Open request from" << std::endl;
	std::cout << "Name: " << _firstName << " " << _lastName << std::endl;
	std::cout << "EGN: " << _EGN << std::endl;
	std::cout << "Age: " << _age << std::endl;
}

void OpenAccountTask::getTaskPreview() const
{
	std::cout<< "Open - " << _firstName <<" " << _lastName << " wants to create an account\n";
}

void OpenAccountTask::writeToFile(std::ofstream& ofs) const
{
	DataPlaceholderTask::writeToFile(ofs);
}

void OpenAccountTask::readFromFile(std::ifstream& ifs)
{
	DataPlaceholderTask::readFromFile(ifs);
}
