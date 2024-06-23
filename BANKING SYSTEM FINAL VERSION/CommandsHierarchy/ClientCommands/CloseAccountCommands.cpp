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
		const Account& ref = bankRef.getAccountById(id);
		
		obj = new CloseAccountTask(ref.getFirstName(), ref.getLastName(), ref.getEGN(), ref.getAge(), bankName, ref.getId(), ref.getBalance());

		bankRef.assignTask(obj);
	}
	catch (std::invalid_argument& e)
	{
		delete obj;
		std::cout << e.what() << std::endl << std::endl;
	}
}
