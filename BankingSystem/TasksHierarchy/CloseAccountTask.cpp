#include "CloseAccountTask.h"

CloseAccountTask::CloseAccountTask(const Account* accPtr) : AccountPlaceholderTask(TaskType::Close, accPtr)
{}

Task* CloseAccountTask::clone() const
{
	return new CloseAccountTask(*this);
}

void CloseAccountTask::getTaskPreview() const
{
	std::cout<< "Close - " << _accPtr->getFirstName() << " " << _accPtr->getLastName() <<
		" wants to close account with id " << _accPtr->getId() << ".\n";
}

void CloseAccountTask::viewTask() const
{
	std::cout << "Close request from" << std::endl;
	std::cout << "Name: " << _accPtr->getFirstName() << " " << _accPtr->getLastName() << std::endl;
	std::cout << "EGN: " << _accPtr->getEGN() << std::endl;
	std::cout << "Age: " << _accPtr->getAge() << std::endl;
	std::cout << "Account Number: " << _accPtr->getId() << std::endl;
	std::cout << "Total Balance: " << _accPtr->getBalance() << std::endl;
}
