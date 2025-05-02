#include "BankerLauncher.h"
#include "../CommandsHierarchy/BankerCommands/ApproveTaskCommands.h"
#include "../CommandsHierarchy/BankerCommands/DisapproveTaskCommands.h"
#include "../CommandsHierarchy/BankerCommands/ShowTasksCommands.h"
#include "../CommandsHierarchy/BankerCommands/ValidateTaskCommands.h"
#include "../CommandsHierarchy/BankerCommands/ViewTaskCommands.h"

void BankerLauncher::printCommands()
{
	std::cout << "Please choose one of those commands: " << std::endl;
	std::cout << "1) Show personal details" << std::endl;
	std::cout << "2) Show this commands menu again" << std::endl;
	std::cout << "3) Preview tasks" << std::endl;
	std::cout << "4) View task in details" << std::endl;
	std::cout << "5) Approve task" << std::endl;
	std::cout << "6) Disapprove task" << std::endl;
	std::cout << "7) Validate task" << std::endl;
	std::cout << "8) Log out" << std::endl<<std::endl;
}

void BankerLauncher::launchBanker(Banker* banker, BankingSystem* bs)
{
	system("CLS");
	printCommands();

	ApproveTaskCommands approve(*banker);
	DisapproveTaskCommands disapprove(*banker);
	ValidateTaskCommands validate(*banker);
	ShowTasksCommands show(*banker);
	ViewTaskCommands view(*banker);

	unsigned command = 0;

	while (true)
	{
		std::cout << "Please enter a command you want to perform>> ";
		std::cin >> command;

		switch (command)
		{
		case 1:
			banker->whoAmI();
			std::cout << std::endl;
			break;
		case 2:
			printCommands();
			break;
		case 3:
			show.execute(bs);
			break;
		case 4:
			view.execute(bs);
			break;
		case 5:
			approve.execute(bs);
			break;
		case 6:
			disapprove.execute(bs);
			break;
		case 7:
			validate.execute(bs);
			break;
		case 8:
			bs->logOut();
			system("CLS");
			return;
		default:
			std::cout << "Invalid command! Try again!" << std::endl << std::endl;
			break;
		}
	}

}
