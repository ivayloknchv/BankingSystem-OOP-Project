#pragma once
#include "Task.h"
#include "AccountPlaceholderTask.h"

class ChangeBankTask : public AccountPlaceholderTask
{
private:

	MyString _newBank = "Unknown";

public:

	ChangeBankTask(const Account* ptr, const MyString& newBank);
	ChangeBankTask(const Account* ptr, MyString&& newBank);

	Task* clone() const override;
	void viewTask() const override;
	void getTaskPreview() const override;
};

