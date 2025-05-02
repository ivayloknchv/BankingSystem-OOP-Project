#include "ShowMessagesCommand.h"

Command* ShowMessagesCommand::clone() const
{
	return new ShowMessagesCommand(*this);
}

void ShowMessagesCommand::execute(BankingSystem* system)
{
	try
	{
		system->viewMessages();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
