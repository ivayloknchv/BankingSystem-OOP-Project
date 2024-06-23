#include "ShowMessagesCommands.h"

ShowMessagesCommands::ShowMessagesCommands(const Client& ref) : _ref(ref), ClientCommands()
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
