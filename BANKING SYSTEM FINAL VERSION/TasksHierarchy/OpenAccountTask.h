#pragma once
#include "../Helpers/MyString.h"
#include "Task.h"
#include "DataPlaceholderTask.h"

class OpenAccountTask : public DataPlaceholderTask
{
private:
	
public:

	OpenAccountTask();
	OpenAccountTask(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age);
	OpenAccountTask(MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age);

	Task* clone() const override;

	void viewTask() const override;
	void getTaskPreview() const override;

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

