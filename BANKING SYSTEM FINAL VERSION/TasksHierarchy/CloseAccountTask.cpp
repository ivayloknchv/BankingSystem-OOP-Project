#include "CloseAccountTask.h"

CloseAccountTask::CloseAccountTask() : AccountPlaceholderTask(TaskType::Close)
{
}

CloseAccountTask::CloseAccountTask(const MyString& firstName, const MyString& lastName,
	const MyString& EGN, unsigned age, const MyString& currentBank, unsigned accId, double balance) :
	AccountPlaceholderTask(TaskType::Close, firstName, lastName, EGN, age, currentBank, accId, balance)
{}

Task* CloseAccountTask::clone() const
{
	return new CloseAccountTask(*this);
}

void CloseAccountTask::getTaskPreview() const
{
	std::cout<< "Close - " << _firstName << " " << _lastName <<
		" wants to close account with id " << _accId << ".\n";
}

void CloseAccountTask::viewTask() const
{
	std::cout << "Close request from" << std::endl;
	std::cout << "Name: " << _firstName << " " << _lastName << std::endl;
	std::cout << "EGN: " << _EGN << std::endl;
	std::cout << "Age: " << _age << std::endl;
	std::cout << "Account Number: " << _accId << std::endl;
	std::cout << "Total Balance: " << _balance << std::endl;
}

void CloseAccountTask::writeToFile(std::ofstream& ofs) const
{
	AccountPlaceholderTask::writeToFile(ofs);
}

void CloseAccountTask::readFromFile(std::ifstream& ifs)
{
	AccountPlaceholderTask::readFromFile(ifs);
}
