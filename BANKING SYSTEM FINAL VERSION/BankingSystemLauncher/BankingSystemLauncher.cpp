#include "BankingSystemLauncher.h"
#include "../CommandsHierarchy/CommandFactory.h"


void BankingSystemLauncher::run()
{
	BankingSystem& system = BankingSystem::getInstance();
	MyString cmd = "";
	
	while(cmd != "stop")
	{
		std::cout << "Enter you command here>> ";
		std::cin >> cmd;

		polymorphic_ptr<Command> command = CommandFactory::createCommand(cmd);

		if (!command.get())
		{
			std::cout << "Invalid command!" << std::endl;
		}
		else
		{
			command->execute(&system);
		}

		std::cout << std::endl << std::endl;
	} 
}
