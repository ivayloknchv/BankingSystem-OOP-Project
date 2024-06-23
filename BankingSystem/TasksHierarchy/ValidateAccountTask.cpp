#include "ValidateAccountTask.h"
#include <utility>

ValidateAccountTask::ValidateAccountTask(const MyString& otherBank, const Account* accPtr) :
	AccountPlaceholderTask(TaskType::Validate, accPtr), _otherBank(otherBank)
{}

ValidateAccountTask::ValidateAccountTask(MyString&& otherBank, const Account* accPtr):
	AccountPlaceholderTask(TaskType::Validate, accPtr), _otherBank(std::move(otherBank))
{}

Task* ValidateAccountTask::clone() const
{
	return new ValidateAccountTask(*this);
}

void ValidateAccountTask::getTaskPreview() const
{
	std::cout<< "Change - " << _otherBank << " asks if "<<_accPtr->getFirstName() << " " << _accPtr->getLastName() << " is real user.\n";
}

void ValidateAccountTask::viewTask() const
{
	std::cout << "Validate request from" << std::endl;
	std::cout << "Name: " << _accPtr->getFirstName() << " " << _accPtr->getLastName() << std::endl;
	std::cout << "EGN: " << _accPtr->getEGN() << std::endl;
	std::cout << "Age: " << _accPtr->getAge() << std::endl;
	std::cout << "Account Number: " << _accPtr->getId() << std::endl;
	std::cout << "Total Balance: " << _accPtr->getBalance() << std::endl;
}
