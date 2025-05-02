#include "CloseAccountCommands.h"
#include "../../TasksHierarchy/CloseAccountTask.h"

CloseAccountCommands::CloseAccountCommands(Client& ref) : ClientCommands(ref)
{
}

Commands* CloseAccountCommands::clone() const
{
	return new CloseAccountCommands(*this);
}

void CloseAccountCommands::execute(BankingSystem* system)
{
	MyString bankName;
	unsigned id = 0;

	std::cout << "Enter bank name>> ";
	std::cin >> bankName;

	std::cout << "Enter account ID>> ";
	std::cin >> id;

	Task* obj = nullptr;

	try
	{
		Bank& bankRef = system->getBankByName(bankName);
		const Account& accRef = bankRef.getAccountById(id);
		
		if (accRef.getEGN() != _ref.getEGN())
		{
			throw std::invalid_argument("Trying to access someone else's account!");
		}

		obj = new CloseAccountTask(accRef.getFirstName(), accRef.getLastName(), accRef.getEGN(), accRef.getAge(), bankName, accRef.getId(), accRef.getBalance());

		bankRef.assignTask(obj);
	}
	catch (std::invalid_argument& e)
	{
		delete obj;
		std::cout << e.what() << std::endl << std::endl;
	}
}
