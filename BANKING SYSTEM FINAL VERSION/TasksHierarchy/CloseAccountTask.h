#pragma once
#include "Task.h"

class CloseAccountTask : public Task
{
	MyString _bankName;
	unsigned _accountId = 0;
	double _balance = 0;

public:

	CloseAccountTask();
	CloseAccountTask(const MyString& firstName, const MyString& lastName,
		const MyString& EGN, unsigned age, const MyString& bankName, unsigned accountId, double balance);
	CloseAccountTask(MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age,
		MyString&& bankName, unsigned accountId, double balance);

	Task* clone() const override;

	void getTaskPreview() const override;
	void viewTask() const override;

	virtual void approve() const override;
	void disapprove() const override;

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

