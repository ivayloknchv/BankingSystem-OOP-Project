#pragma once
#include "User.h"
#include "Task.h"
#include "MyVector.hpp"
#include "polymorphic_ptr.hpp"

class Banker : public User
{
	MyVector<polymorphic_ptr<Task>> tasks;

public:

	Banker() = default;
	Banker(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age);
	Banker(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age);

	void whoAmI() const override;

	User* clone() const override;

	void addTask(Task* ptr);
	
	void addTask(const Task& obj);

	void previewTasks() const;

	void viewTak(size_t idx) const;

	size_t getTasksCount() const;
};

