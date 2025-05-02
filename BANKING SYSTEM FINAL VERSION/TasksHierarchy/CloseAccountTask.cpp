#include "CloseAccountTask.h"
#include "../Components/BankingSystem.h"

CloseAccountTask::CloseAccountTask() : Task(TaskType::Close)
{
}

CloseAccountTask::CloseAccountTask(const MyString& firstName, const MyString& lastName,
	const MyString& EGN, unsigned age, const MyString& bankName, unsigned accountId, double balance) :
	Task(TaskType::Close, firstName, lastName, EGN, age), _bankName(bankName), _accountId(accountId), _balance(balance)
{}

CloseAccountTask::CloseAccountTask(MyString && firstName, MyString && lastName, MyString&& EGN, unsigned age, 
	MyString && bankName, unsigned accountId, double balance) : Task(TaskType::Close, std::move(firstName), std::move(lastName),
		std::move(EGN), age), _bankName(std::move(bankName)), _accountId(accountId), _balance(balance)
{
}

Task* CloseAccountTask::clone() const
{
	return new CloseAccountTask(*this);
}

void CloseAccountTask::getTaskPreview() const
{
	std::cout<< "Close - " << _firstName << " " << _lastName <<
		" wants to close account with id " << _accountId << '.' << std::endl;
}

void CloseAccountTask::viewTask() const
{
	std::cout << "Close request from" << std::endl;
	Task::viewTask();
	std::cout << "Account Number: " << _accountId << std::endl;
	std::cout << "Total Balance: " << _balance << std::endl;
}

void CloseAccountTask::writeToFile(std::ofstream& ofs) const
{
	Task::writeToFile(ofs);
	writeStringToFile(ofs, _bankName);
	ofs.write((const char*)&_accountId, sizeof(unsigned));
	ofs.write((const char*)&_balance, sizeof(double));
}

void CloseAccountTask::readFromFile(std::ifstream& ifs)
{
	Task::readFromFile(ifs);
	_bankName = readStringFromFile(ifs);
	ifs.read((char*)&_accountId, sizeof(unsigned));
	ifs.read((char*)&_balance, sizeof(double));
}

void CloseAccountTask::approve() const
{
	BankingSystem& system = BankingSystem::getInstance();
	system.getBankByName(_bankName).removeAccountByID(_accountId);
	system.getClientByEGN(_EGN).addMessage(std::move(Message("Removed your account from " + _bankName)));
}

void CloseAccountTask::disapprove() const
{
	std::cout << "Enter reason to disapprove>> ";
	char buff[1024]{};
	std::cin.getline(buff, 1024);

	BankingSystem& system = BankingSystem::getInstance();

	MyString msg = "Your request to close an account in " + _bankName + " was rejected. Reason: " + msg;
	system.getClientByEGN(_EGN).addMessage(std::move(Message(msg)));
}
