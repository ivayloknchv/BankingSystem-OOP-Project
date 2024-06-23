#pragma once
#include "../UsersHierarchy/User.h"
#include "../TasksHierarchy/Task.h"
#include "../Helpers/MyVector.hpp"
#include "../Helpers/polymorphic_ptr.hpp"

class Banker : public User
{
	MyString _workplace = "Unknown bank";

	MyVector<polymorphic_ptr<Task>> tasks;

public:

	Banker() = default;
	Banker(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age, const MyString& workplace);
	Banker(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age, MyString&& workplace);

	void whoAmI() const override;
	User* clone() const override;

	const MyString& getWorkplace() const;

	void addTask(Task* ptr);
	void addTask(const Task& obj);

	void removeTaskAt(size_t idx);
	void previewTasks() const;
	void viewTask(size_t idx) const;

	size_t getTasksCount() const;
	const Task* getTask(size_t idx) const;
	Task* getTask(size_t idx);

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

