#pragma once
#include "AccountPlaceholderTask.h"
#include "Account.h"

class ValidateAccountTask : public AccountPlaceholderTask
{
	MyString _otherBank = "Unknown";
	
public:

	ValidateAccountTask(const MyString& otherBank, const Account* accPtr);
	ValidateAccountTask(MyString&& otherBank, const Account* accPtr);

	Task* clone() const override;

	void getTaskPreview() const override;

	void viewTask() const override;

};

