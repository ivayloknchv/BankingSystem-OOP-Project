#include "Banker.h"
#include <utility>
#include <iostream>
#include <stdexcept>
#include "../TasksHierarchy/TaskFactory.h"

Banker::Banker(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age, const MyString& workplace)
	:User(firstName, lastName, EGN, password, age), _workplace(workplace)
{
}

Banker::Banker(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age, MyString&& workplace)
	:User(std::move(firstName), std::move(lastName), std::move(EGN), std::move(password), age), _workplace(std::move(workplace))
{
}

void Banker::whoAmI() const
{
	User::whoAmI();
	std::cout << "Status: Banker" << std::endl;
}

User* Banker::clone() const
{
	return new Banker(*this);
}

void Banker::addTask(Task* ptr)
{
	tasks.push_back(ptr);
}

void Banker::addTask(const polymorphic_ptr<Task>& task)
{
	tasks.push_back(task);
}

void Banker::removeTaskAt(size_t idx)
{
	if (idx <= 0 || idx > tasks.size())
	{
		throw std::invalid_argument("Invalid index!");
	}

	tasks.erase(idx - 1);
}

void Banker::previewTasks() const
{
	size_t size = tasks.size();

	if (size == 0)
	{
		std::cout << "No tasks assigned!" << std::endl;
	}

	for (size_t i = 0; i < size; i++)
	{
		std::cout << '[' << i + 1 << "] ";
		tasks[i]->getTaskPreview();
	}
}

void Banker::viewTask(size_t idx) const
{
	if (getTasksCount() == 0)
	{
		throw std::invalid_argument("No tasks assigned!");
	}

	if (idx <= 0 || idx > tasks.size())
	{
		throw std::invalid_argument("Invalid range!");
	}

	tasks[idx - 1]->viewTask();
}

size_t Banker::getTasksCount() const
{
	return tasks.size();
}

const MyString& Banker::getWorkplace() const
{
	return _workplace;
}

const Task* Banker::getTask(size_t idx) const
{
	if (getTasksCount() == 0)
	{
		throw std::invalid_argument("No tasks assigned!");
	}

	if (idx <= 0 || idx > tasks.size())
	{
		throw std::invalid_argument("Invalid range!");
	}

	return tasks[idx - 1].get();
}

Task* Banker::getTask(size_t idx)
{
	if (getTasksCount() == 0)
	{
		throw std::invalid_argument("No tasks assigned!");
	}

	if (idx <= 0 || idx > tasks.size())
	{
		throw std::invalid_argument("Invalid range!");
	}

	return tasks[idx - 1].get();
}

void Banker::writeToFile(std::ofstream& ofs) const
{
	User::writeToFile(ofs);

	writeStringToFile(ofs, _workplace);

	size_t tasksCount = tasks.size();

	ofs.write((const char*)&tasksCount, sizeof(size_t));

	for (size_t i = 0; i < tasksCount; i++)
	{
		tasks[i]->writeToFile(ofs);
	}
}

void Banker::readFromFile(std::ifstream& ifs)
{
	User::readFromFile(ifs);

	_workplace = readStringFromFile(ifs);

	size_t taskCount = 0;

	ifs.read((char*)&taskCount, sizeof(size_t));

	for (size_t i = 0; i < taskCount; i++)
	{
		tasks.push_back(TaskFactory::create(ifs));
	}
}
