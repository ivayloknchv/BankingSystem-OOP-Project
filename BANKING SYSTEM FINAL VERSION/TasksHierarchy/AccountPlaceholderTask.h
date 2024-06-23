#pragma once
#include "DataPlaceholderTask.h"
#include "../Components/Account.h"

class AccountPlaceholderTask : public DataPlaceholderTask
{
protected:

	MyString _currentBank = "Unknown";
	unsigned _accId = 0;
	double _balance = 0.0;

public:

	AccountPlaceholderTask(TaskType type);

	AccountPlaceholderTask(TaskType type, const MyString& firstName, const MyString& lastName, 
		const MyString& EGN, unsigned age, const MyString& currentBank, unsigned accId, double balance);

	unsigned getAccountId() const;
	double getBalance() const;
	const MyString& getCurrentBank() const;

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

