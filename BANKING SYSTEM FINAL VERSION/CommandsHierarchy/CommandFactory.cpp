#include "CommandFactory.h"
#include "BankingSystemCommands/SignUpCommand.h"
#include "BankingSystemCommands/LogInCommand.h"
#include "BankingSystemCommands/CreateBankCommand.h"
#include "BankingSystemCommands/WhoAmICommand.h"
#include "BankingSystemCommands/HelpCommand.h"
#include "BankingSystemCommands/ExitCommand.h"
#include "ClientCommands/CheckAvlCommand.h"
#include "ClientCommands/OpenAccountCommand.h"
#include "ClientCommands/CloseAccountCommand.h"
#include "ClientCommands/RedeemChequeCommand.h"
#include "ClientCommands/ChangeBankCommand.h"
#include "ClientCommands/ListAccountsCommand.h"
#include "ClientCommands/ShowMessagesCommand.h"
#include "BankerCommands/ShowTasksCommand.h"
#include "BankerCommands/ViewTaskCommand.h"
#include "BankerCommands/ApproveTaskCommand.h"
#include "BankerCommands/DisapproveTaskCommand.h"
#include "BankerCommands/ValidateTaskCommand.h"
#include "ThirdPartyCommands/SendChequeCommand.h"

polymorphic_ptr<Command> CommandFactory::createCommand(const MyString& command)
{
	if (command == "signup")
	{
		return new SignUpCommand();
	}
	else if (command == "login")
	{
		return new LogInCommand();
	}
	else if (command == "exit")
	{
		return new ExitCommand();
	}
	else if (command == "whoami")
	{
		return new WhoAmICommand();
	}
	else if (command == "help")
	{
		return new HelpCommand();
	}
	else if (command == "create_bank")
	{
		return new CreateBankCommand();
	}
	else if (command == "check_avl")
	{
		return new CheckAvlCommand();
	}
	else if (command == "open")
	{
		return new OpenAccountCommand();
	}
	else if (command == "close")
	{
		return new CloseAccountCommand();
	}
	else if (command == "redeem")
	{
		return new RedeemChequeCommand();
	}
	else if (command == "change")
	{
		return new ChangeBankCommand();
	}
	else if (command == "list")
	{
		return new ListAccountsCommand();
	}
	else if (command == "messages")
	{
		return new ShowMessagesCommand();
	}
	else if (command == "tasks")
	{
		return new ShowTasksCommand();
	}
	else if (command == "view")
	{
		return new ViewTaskCommand();
	}
	else if (command == "approve")
	{
		return new ApproveTaskCommand();
	}
	else if (command == "disapprove")
	{
		return new DisapproveTaskCommand();
	}
	else if (command == "validate")
	{
		return new ValidateTaskCommand();
	}
	else if (command == "send_cheque")
	{
		return new SendChequeCommand();
	}

	return nullptr;
}
