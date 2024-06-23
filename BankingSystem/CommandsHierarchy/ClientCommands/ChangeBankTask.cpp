#include "ChangeBankTask.h"

ChangeBankTask::ChangeBankTask(const Account* ptr, const MyString& newBank) : 
	AccountPlaceholderTask(TaskType::Change, ptr) , _newBank(newBank)
{
}

ChangeBankTask::ChangeBankTask(const Account* ptr, MyString&& newBank) :
	AccountPlaceholderTask(TaskType::Change, ptr), _newBank(std::move(newBank))
{
}

Task* ChangeBankTask::clone() const
{
	return new ChangeBankTask(*this);
}

void ChangeBankTask::viewTask() const
{
	std::cout << "Change request from" << std::endl;
	std::cout << "Name: " << _accPtr->getFirstName() << " " << _accPtr->getLastName() << std::endl;
	std::cout << "EGN: " << _accPtr->getEGN() << std::endl;
	std::cout << "Age: " << _accPtr->getAge() << std::endl;
	std::cout << "Bank: " << _accPtr->getBankName() << std::endl;
}

void ChangeBankTask::getTaskPreview() const
{
	std::cout<< "Change - " << _accPtr->getFirstName() << " " << _accPtr->getLastName() << "wants to join " << _accPtr->getBankName() << ".\n";
}
