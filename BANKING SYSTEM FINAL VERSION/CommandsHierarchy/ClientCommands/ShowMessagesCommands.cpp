#include "ShowMessagesCommands.h"

ShowMessagesCommands::ShowMessagesCommands(Client& ref) :  ClientCommands(ref)
{
}

Commands* ShowMessagesCommands::clone() const
{
	return new ShowMessagesCommands(*this);
}

void ShowMessagesCommands::execute(BankingSystem* system)
{
	_ref.listMessages();
	std::cout<<std::endl;
}
