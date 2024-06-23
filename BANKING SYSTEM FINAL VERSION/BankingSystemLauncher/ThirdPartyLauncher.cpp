#include "ThirdPartyLauncher.h"

void ThirdPartyLauncher::printCommands()
{
	std::cout << "Please choose one of those commands: " << std::endl;
	std::cout << "1) Show personal details" << std::endl;
	std::cout << "2) Show this commands menu again" << std::endl;
	std::cout << "3) Send cheque" << std::endl;
	std::cout << "4) Log out" << std::endl << std::endl;
}

void ThirdPartyLauncher::manageThirdParty(ThirdPartyEmployee* emp, BankingSystem* bs)
{
	system("CLS");
	printCommands();
	SendChequeCommands sendCheque(*emp);

	unsigned command = 0;

	while (true)
	{
		std::cout << "Please enter a command you want to perform>> ";
		std::cin >> command;

		switch (command)
		{
		case 1:
			emp->whoAmI();
			std::cout << std::endl;
			break;
		case 2:
			printCommands();
			break;
		case 3:
			sendCheque.execute(bs);
			break;
		case 4:
			bs->logOut();
			system("CLS");
			return;
		default:
			std::cout << "Invalid command! Try again!" << std::endl << std::endl;
			break;
		}
	}
}
