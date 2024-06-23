#include "AccountPlaceholderTask.h"

AccountPlaceholderTask::AccountPlaceholderTask(TaskType type) : DataPlaceholderTask(type)
{
}

AccountPlaceholderTask::AccountPlaceholderTask(TaskType type, const MyString& firstName, const MyString& lastName,
	const MyString& EGN, unsigned age, const MyString& currentBank, unsigned accId, double balance) :
	DataPlaceholderTask(type, firstName, lastName, EGN, age), _currentBank(currentBank), _accId(accId), _balance(balance)
{}

unsigned AccountPlaceholderTask::getAccountId() const
{
	return _accId;
}

double AccountPlaceholderTask::getBalance() const
{
	return _balance;
}

const MyString& AccountPlaceholderTask::getCurrentBank() const
{
	return _currentBank;
}

void AccountPlaceholderTask::writeToFile(std::ofstream& ofs) const
{
	DataPlaceholderTask::writeToFile(ofs);

	writeStringToFile(ofs, _currentBank);
	ofs.write((const char*)&_accId, sizeof(unsigned));
	ofs.write((const char*)&_balance, sizeof(double));
}

void AccountPlaceholderTask::readFromFile(std::ifstream& ifs)
{
	DataPlaceholderTask::readFromFile(ifs);

	_currentBank = readStringFromFile(ifs);
	ifs.read((char*)&_accId, sizeof(unsigned));
	ifs.read((char*)&_balance, sizeof(double));
}

