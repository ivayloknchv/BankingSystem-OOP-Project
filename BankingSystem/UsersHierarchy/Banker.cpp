#include "Banker.h"
#include <utility>
#include <iostream>
#include <stdexcept>

Banker::Banker(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age)
	:User(firstName, lastName, EGN, password, age)
{
}

Banker::Banker(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age)
	:User(std::move(firstName), std::move(lastName), std::move(EGN), std::move(password), age)
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

void Banker::addTask(const Task& obj)
{
	tasks.push_back(obj.clone());
}

void Banker::previewTasks() const
{
	size_t size = tasks.size();

	for (size_t i = 0; i < size; i++)
	{
		std::cout << '[' << i + 1 << "] ";
		tasks[i]->getTaskPreview();
	}
}

void Banker::viewTak(size_t idx) const
{
	if (idx<0 || idx>tasks.size())
	{
		throw std::out_of_range("Invalid range!");
	}

	tasks[idx - 1]->viewTask();
}

size_t Banker::getTasksCount() const
{
	return tasks.size();
}
