#pragma once
#include "../Helpers/MyString.h"
#include "Task.h"


class OpenAccountTask : public Task
{
private:
	MyString _bankName;
public:

	OpenAccountTask();
	OpenAccountTask(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& bankName);
	OpenAccountTask(MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age, MyString&& bankName);

	Task* clone() const override;

	void viewTask() const override;
	void getTaskPreview() const override;

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;

	void approve() const override;
	void disapprove() const override;
};

