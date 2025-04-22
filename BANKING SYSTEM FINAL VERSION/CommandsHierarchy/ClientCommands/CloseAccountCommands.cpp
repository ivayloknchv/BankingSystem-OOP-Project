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

	try
	{
		const Bank& bankRef = system->getBankByName(bankName);
		const Account& accRef = bankRef.getAccountById(id);
		
		if (accRef.getEGN() != _ref.getEGN())
		{
			throw std::exception("Trying to access someone else's account!");
		}

		polymorphic_ptr<Task> task = new CloseAccountTask(accRef.getFirstName(), accRef.getLastName(), accRef.getEGN(), 
			accRef.getAge(), bankName, accRef.getId(), accRef.getBalance());
		system->assignTaskToBank(bankName, task);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}
