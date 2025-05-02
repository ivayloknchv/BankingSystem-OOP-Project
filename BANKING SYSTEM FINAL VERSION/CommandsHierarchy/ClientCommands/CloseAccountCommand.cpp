#include "CloseAccountCommand.h"

Command* CloseAccountCommand::clone() const
{
	return new CloseAccountCommand(*this);
}

void CloseAccountCommand::execute(BankingSystem* system)
{
	MyString bankName;
	unsigned accountId = 0;

	std::cin >> bankName >> accountId;

	try
	{
		system->closeAccount(bankName, accountId);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
