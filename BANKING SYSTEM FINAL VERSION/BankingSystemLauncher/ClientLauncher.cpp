#include "ClientLauncher.h"
#include "../CommandsHierarchy/ClientCommands/ChangeBankCommands.h"
#include "../CommandsHierarchy/ClientCommands/CheckAvlCommands.h"
#include "../CommandsHierarchy/ClientCommands/CloseAccountCommands.h"
#include "../CommandsHierarchy/ClientCommands/ListAccountsCommands.h"
#include "../CommandsHierarchy/ClientCommands/OpenAccountCommands.h"
#include "../CommandsHierarchy/ClientCommands/RedeemChequeCommands.h"
#include "../CommandsHierarchy/ClientCommands/ShowMessagesCommands.h"

void ClientLauncher::printCommands()
{
	std::cout << "Please choose one of those commands: " << std::endl;
	std::cout << "1) Show personal details" << std::endl;
	std::cout << "2) Show this commands menu again" << std::endl;
	std::cout << "3) Check account balance" << std::endl;
	std::cout << "4) Open a new bank account" << std::endl;
	std::cout << "5) Close bank account" << std::endl;
	std::cout << "6) Redeem cheque" << std::endl;
	std::cout << "7) Change bank" << std::endl;
	std::cout << "8) List all accounts in a bank" << std::endl;
	std::cout << "9) Show messages" << std::endl;
	std::cout << "10) Log out" << std::endl << std::endl;
}

void ClientLauncher::manageClient(Client* client, BankingSystem* bs)
{
	system("CLS");
	printCommands();

	CheckAvlCommands checkAvl(*client);
	CloseAccountCommands closeAcc(*client);
	OpenAccountCommands openAcc(*client);
	ChangeBankCommands changeBank(*client);
	RedeemChequeCommands redeem(*client);
	ShowMessagesCommands showMsg(*client);
	ListAccountsCommands listAcc(*client);

	unsigned command = 0;

	while (true)
	{
		std::cout << "Please enter a command you want to perform>> ";
		std::cin >> command;

		switch (command)
		{
		case 1:
			client->whoAmI();
			std::cout << std::endl;
			break;

		case 2:
			printCommands();
			break;

		case 3:
			checkAvl.execute(bs);
			break;

		case 4:
			openAcc.execute(bs);
			break;

		case 5:
			closeAcc.execute(bs);
			break;

		case 6:
			redeem.execute(bs);
			break;

		case 7:
			changeBank.execute(bs);
			break;
		case 8:
			listAcc.execute(bs);
			break;

		case 9: 
			showMsg.execute(bs);
			break;

		case 10:
			bs->logOut();
			system("CLS");
			return;

		default:
			std::cout << "Invalid command! Try again!" << std::endl << std::endl;
			break;
		}
	}
}
