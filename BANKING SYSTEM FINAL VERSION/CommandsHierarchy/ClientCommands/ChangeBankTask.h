#pragma once
#include "../../TasksHierarchy/Task.h"
#include "../../TasksHierarchy/AccountPlaceholderTask.h"

enum class Status
{
	Waiting,
	Approved,
	Rejected
};

class ChangeBankTask : public AccountPlaceholderTask
{
private:

	Status _status = Status::Waiting;
	MyString _newBank = "Unknown";

	void printStatus() const;
public:

	ChangeBankTask(const Account* ptr, const MyString& newBank);
	ChangeBankTask(const Account* ptr, MyString&& newBank);

	Task* clone() const override;
	void viewTask() const override;
	void getTaskPreview() const override;

	Status getStatus() const;

	void changeStatus(Status status);
};

