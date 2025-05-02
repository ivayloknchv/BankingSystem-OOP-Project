#include "ChangeBankTask.h"


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

ChangeBankTask::ChangeBankTask() : AccountPlaceholderTask(TaskType::Change)
{
}

ChangeBankTask::ChangeBankTask(const MyString& firstName, const MyString& lastName,
	const MyString& EGN, unsigned age, const MyString& currentBank, unsigned accId, double balance, const MyString& newBank) :
	AccountPlaceholderTask(TaskType::Change, firstName, lastName, EGN, age, currentBank, accId, balance) , _newBank(newBank)
{}

Task* ChangeBankTask::clone() const
{
	return new ChangeBankTask(*this);
}

void ChangeBankTask::viewTask() const
{
	std::cout << "Change request from" << std::endl;
	std::cout << "Name: " << _firstName << " " <<_lastName << std::endl;
	std::cout << "EGN: " << _EGN << std::endl;
	std::cout << "Age: " << _age << std::endl;
	std::cout << "Bank: " << _currentBank << std::endl;
}

void ChangeBankTask::getTaskPreview() const
{
	printStatus();
	std::cout<< "Change - " << _firstName << " " << _lastName << " wants to join " << _newBank << ".\n";
}

Status ChangeBankTask::getStatus() const
{
	return _status;
}

void ChangeBankTask::changeStatus(Status status)
{
	_status = status;
}

void ChangeBankTask::writeToFile(std::ofstream& ofs) const
{
	AccountPlaceholderTask::writeToFile(ofs);
	ofs.write((const char*)&_status, sizeof(Status));
	writeStringToFile(ofs, _newBank);
}

void ChangeBankTask::readFromFile(std::ifstream& ifs)
{
	AccountPlaceholderTask::readFromFile(ifs);
	ifs.read((char*)&_status, sizeof(Status));
	_newBank = readStringFromFile(ifs);
}
