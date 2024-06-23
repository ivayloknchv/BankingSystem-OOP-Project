#pragma once

#include "Task.h"
#include "AccountPlaceholderTask.h"

enum class Status
{
	NeedsValidation,
	Approved,
	Rejected
};

class ChangeBankTask : public AccountPlaceholderTask
{
private:

	Status _status = Status::NeedsValidation;
	MyString _newBank = "Unknown";

	void printStatus() const;

public:

	ChangeBankTask();

	ChangeBankTask(const MyString& firstName, const MyString& lastName,
		const MyString& EGN, unsigned age, const MyString& currentBank, unsigned accId, double balance, const MyString& newBank);

	Task* clone() const override;
	void viewTask() const override;
	void getTaskPreview() const override;

	Status getStatus() const;

	void changeStatus(Status status);

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

