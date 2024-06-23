#include "OpenAccountCommands.h"
#include "Task.h"
#include "OpenAccountTask.h"

OpenAccountCommands::OpenAccountCommands(const Client& ref) : _ref(ref), ClientCommands()
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
	
	Task* obj = new OpenAccountTask(_ref.getFirstName(), _ref.getLastName(), _ref.getEGN(), _ref.getAge());

	try
	{
		system->getBankByName(bankName).assignTask(obj);
	}

	catch (std::invalid_argument& e)
	{
		delete obj;
		std::cout << e.what() << std::endl << std::endl;
	}
}
