#include "ChangeBankTask.h"
#include "../Components/BankingSystem.h"

void ChangeBankTask::printStatus() const
{
	switch (_status)
	{
	case (Status::NeedsValidation):
		std::cout << " (Needs validation) ";
		break;

	case (Status::Approved):
		std::cout << " (Approved) ";
		break;

	case (Status::Rejected):
		std::cout << " (Rejected) ";
		break;
	}
}

ChangeBankTask::ChangeBankTask() : Task(TaskType::Change)
{
}

ChangeBankTask::ChangeBankTask(const MyString& firstName, const MyString& lastName, const MyString& EGN,
	unsigned age, const MyString& currentBank, unsigned accountId, double balance, const MyString& newBank) :
	Task(TaskType::Change, firstName, lastName, EGN, age) , _currentBank(currentBank), _accountId(accountId), 
	_balance(balance), _newBank(newBank)
{}

Task* ChangeBankTask::clone() const
{
	return new ChangeBankTask(*this);
}

ChangeBankTask::ChangeBankTask(MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age, MyString&& currentBank,
	unsigned accountId, double balance, MyString&& newBank) :
	Task(TaskType::Change, std::move(firstName), std::move(lastName), std::move(EGN), age), _currentBank(std::move(currentBank)), 
	_accountId(accountId), _balance(balance), _newBank(std::move(newBank))
{
}


void ChangeBankTask::viewTask() const
{
	std::cout << "Change request from" << std::endl;
	Task::viewTask();
	std::cout << "Bank: " << _currentBank << std::endl;
	std::cout << "Account ID: " << _accountId << std::endl;
	std::cout << "Balance: " << _balance << std::endl;
}

void ChangeBankTask::getTaskPreview() const
{
	printStatus();
	std::cout<< "Change - " << _firstName << " " << _lastName << " wants to join " << _newBank << ".\n";
}

void ChangeBankTask::writeToFile(std::ofstream& ofs) const
{
	Task::writeToFile(ofs);
	ofs.write((const char*)&_status, sizeof(Status));
	writeStringToFile(ofs, _currentBank);
	ofs.write((const char*)&_accountId, sizeof(unsigned));
	ofs.write((const char*)&_balance, sizeof(double));
	writeStringToFile(ofs, _newBank);
}

void ChangeBankTask::readFromFile(std::ifstream& ifs)
{
	Task::readFromFile(ifs);
	ifs.read((char*)&_status, sizeof(Status));
	_currentBank = readStringFromFile(ifs);
	ifs.read((char*)&_accountId, sizeof(unsigned));
	ifs.read((char*)&_balance, sizeof(double));
	_newBank = readStringFromFile(ifs);
}

void ChangeBankTask::approve() const
{
	if (_status == Status::Approved)
	{
		BankingSystem& system = BankingSystem::getInstance();
		Account newAccount = Account(_firstName, _lastName, _EGN, _age, _newBank);
		newAccount.addBalance(_balance);
		system.getBankByName(_newBank).addAccount(std::move(newAccount));
		system.getClientByEGN(_newBank).addMessage(std::move(Message("Transferred your account from "
			+ _currentBank + " to " + _newBank)));
	}
	else if (_status == Status::NeedsValidation)
	{
		throw std::invalid_argument("Needs a validation from the current bank!");
	}
	else
	{
		throw std::invalid_argument("Account transfer is rejected!");
	}
}

void ChangeBankTask::disapprove() const
{
	std::cout << "Enter reason to disapprove>> ";
	char buff[1024]{};
	std::cin.getline(buff, 1024);

	BankingSystem& system = BankingSystem::getInstance();

	MyString msg = "Your request to transfer an account from " + _currentBank + " to " + _newBank+ " was disapproved. Reason: " + msg;
	system.getClientByEGN(_EGN).addMessage(std::move(Message(msg)));
}

void ChangeBankTask::validate()
{
	BankingSystem& system = BankingSystem::getInstance();

	if (system.getBankByName(_currentBank).accountExists(_accountId))
	{
		_status = Status::Approved;
	}
	else
	{
		_status = Status::Rejected;
	}
}
