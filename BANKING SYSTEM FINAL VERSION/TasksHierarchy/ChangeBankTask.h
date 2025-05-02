#pragma once
#include "Task.h"

enum class Status
{
	NeedsValidation,
	Approved,
	Rejected
};

class ChangeBankTask : public Task
{
private:

	Status _status = Status::NeedsValidation;
	MyString _currentBank;
	unsigned _accountId = 0;
	double _balance = 0;
	MyString _newBank;

	void printStatus() const;

public:

	ChangeBankTask();

	ChangeBankTask(const MyString& firstName, const MyString& lastName, const MyString& EGN,
		unsigned age, const MyString& currentBank, unsigned accountId, double balance, const MyString& newBank);

	ChangeBankTask(MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age, MyString&& currentBank,
		unsigned accountId, double balance, MyString&& newBank);

	Task* clone() const override;
	void viewTask() const override;
	void getTaskPreview() const override;

	void approve() const override;
	void disapprove() const override;
	void validate();

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

