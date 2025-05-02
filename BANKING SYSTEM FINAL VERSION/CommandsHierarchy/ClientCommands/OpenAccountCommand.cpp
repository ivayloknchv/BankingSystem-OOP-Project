#include "OpenAccountCommand.h"

Command* OpenAccountCommand::clone() const
{
	return new OpenAccountCommand(*this);
}

void OpenAccountCommand::execute(BankingSystem* system)
{	
	MyString bankName;
	std::cin >> bankName;
	
	try
	{
		system->openAccount(bankName);
		std::cout << "Successfully sent a request for a new bank account!";
	}

	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
