#include "BankingSystemLauncher.h"
#include "../CommandsHierarchy/BankingSystemCommands/CreateBankCommands.h"
#include "../CommandsHierarchy/BankingSystemCommands/LogInCommands.h"
#include "../CommandsHierarchy/BankingSystemCommands/SignUpCommands.h"
#include "ClientLauncher.h"
#include "ThirdPartyLauncher.h"
#include "BankerLauncher.h"

void BankingSystemLauncher::printCommands()
{
	std::cout << "	-----BANKING SYSTEM-----	" << std::endl << std::endl;
	std::cout << "Please choose one of these system commands: " << std::endl;
	std::cout << "1) Create Bank" << std::endl;
	std::cout << "2) Log in" << std::endl;
	std::cout << "3) Sign up" << std::endl;
	std::cout << "4) Exit system" << std::endl;
	std::cout << "5) Show commands menu again" << std::endl;
	std::cout << std::endl;
}

void BankingSystemLauncher::handleLoggedUser(BankingSystem& system)
{
	LoggedType loggedType = system.getLoggedType();
	User* logged = system.getLoggedUser();

	switch (loggedType)
	{
	case (LoggedType::Unknown):
		break;

	case (LoggedType::Banker):
		BankerLauncher::launchBanker(static_cast<Banker*>(logged), &system);
		break;

	case (LoggedType::Client):
		ClientLauncher::manageClient(static_cast<Client*>(logged), &system);
		break;

	case (LoggedType::ThirdParty):
		ThirdPartyLauncher::manageThirdParty(static_cast<ThirdPartyEmployee*>(logged), &system);
		break;
	}
}

void BankingSystemLauncher::run()
{
	BankingSystem& bs=BankingSystem::getInstance();
	bs.readFromFile();
	CreateBankCommands createBank;
	SignUpCommands signUp;
	LogInCommands logIn;

	unsigned command = 0;

	printCommands();

	while (true)
	{
		std::cout << "Enter a command you want to perform>> ";
		std::cin >> command;
		std::cout << std::endl;

		switch (command)
		{
		case 1:
			createBank.execute(&bs);
			break;

		case 2:
			logIn.execute(&bs);
			handleLoggedUser(bs);
			printCommands();
			break;

		case 3:
			signUp.execute(&bs);
			break;
			
		case 4:
			bs.writeToFile();
			std::cout << "Successfully exited the system!" << std::endl << std::endl;
			return;

		case 5:
			printCommands();
			break;

		default :
			std::cout << "Invalid command! Try again!" << std::endl<<std::endl;
			break;
		}
	}	
}
