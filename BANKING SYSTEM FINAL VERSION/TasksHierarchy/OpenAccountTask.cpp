#include "OpenAccountTask.h"
#include <utility>
#include <iostream>
#include "../Components/BankingSystem.h"

OpenAccountTask::OpenAccountTask() : Task(TaskType::Open)
{
}

OpenAccountTask::OpenAccountTask(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& bankName):
	Task(TaskType::Open, firstName, lastName, EGN, age), _bankName(bankName)
{}

OpenAccountTask::OpenAccountTask(MyString && firstName, MyString && lastName, MyString && EGN, unsigned age, MyString&& bankName):
	Task(TaskType::Open, std::move(firstName), std::move(lastName), std::move(EGN), age), _bankName(std::move(bankName))
{}

Task* OpenAccountTask::clone() const
{
	return new OpenAccountTask(*this);
}

void OpenAccountTask::viewTask() const
{
	std::cout << "Open request from" << std::endl;
	Task::viewTask();
	std::cout << "Bank: " << _bankName << std::endl;
}

void OpenAccountTask::getTaskPreview() const
{
	std::cout<< "Open - " << _firstName <<" " << _lastName << " wants to create an account\n";
}

void OpenAccountTask::writeToFile(std::ofstream& ofs) const
{
	Task::writeToFile(ofs);
	writeStringToFile(ofs, _bankName);
}

void OpenAccountTask::readFromFile(std::ifstream& ifs)
{
	Task::readFromFile(ifs);
	_bankName = readStringFromFile(ifs);
}

void OpenAccountTask::approve() const
{
	BankingSystem& system = BankingSystem::getInstance();
	system.getBankByName(_bankName).addAccount(std::move(Account(_firstName, _lastName, _EGN, _age, _bankName)));
	system.sendMessage(_EGN, std::move(Message("Created an account in " + _bankName)));
}

void OpenAccountTask::disapprove() const
{
	std::cout << "Enter reason to disapprove>> ";
	char buff[1024]{};
	std::cin.getline(buff, 1024);

	BankingSystem& system = BankingSystem::getInstance();

	MyString msg = "Your request to open an account in " + _bankName + " was disapproved. Reason: " + msg;
	system.sendMessage(_EGN, (std::move(Message(msg))));
}
