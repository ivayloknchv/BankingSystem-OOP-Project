#pragma once
#include "AccountPlaceholderTask.h"
#include "../Components/Account.h"

class CloseAccountTask : public AccountPlaceholderTask
{

public:

	CloseAccountTask();
	CloseAccountTask(const MyString& firstName, const MyString& lastName,
		const MyString& EGN, unsigned age, const MyString& currentBank, unsigned accId, double balance);

	Task* clone() const override;

	void getTaskPreview() const override;
	void viewTask() const override;

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

