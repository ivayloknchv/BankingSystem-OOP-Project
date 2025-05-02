#include "OpenAccountCommands.h"
#include "../../TasksHierarchy/Task.h"
#include "../../TasksHierarchy/OpenAccountTask.h"

OpenAccountCommands::OpenAccountCommands(Client& ref) :  ClientCommands(ref)
{
}

Commands* OpenAccountCommands::clone() const
{
	return new OpenAccountCommands(*this);
}

void OpenAccountCommands::execute(BankingSystem* system)
{
	
	MyString bankName;

	std::cout << "Enter bank name>> ";
	std::cin >> bankName;
	std::cout << std::endl;
	
	try
	{
		polymorphic_ptr<Task> task = new OpenAccountTask(_ref.getFirstName(), _ref.getLastName(), _ref.getEGN(), _ref.getAge());
		system->assignTaskToBank(bankName, task);
		std::cout << "Successfully sent a request for a new bank account!" << std::endl << std::endl;
	}

	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}
