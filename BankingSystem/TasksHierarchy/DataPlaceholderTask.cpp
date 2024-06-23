#include "DataPlaceholderTask.h"

DataPlaceholderTask::DataPlaceholderTask(TaskType type, const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age)
	:Task(type), _firstName(firstName), _lastName(lastName), _EGN(EGN), _age(age)
{}

DataPlaceholderTask::DataPlaceholderTask(TaskType type, MyString && firstName, MyString && lastName, MyString && EGN, unsigned age)
	:Task(type), _firstName(std::move(firstName)), _lastName(std::move(lastName)), _EGN(std::move(EGN)), _age(age)
{}

