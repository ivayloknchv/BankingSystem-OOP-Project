#include "DisapproveTaskCommands.h"
#include "../../TasksHierarchy/OpenAccountTask.h"
#include "../../TasksHierarchy/AccountPlaceholderTask.h"

void DisapproveTaskCommands::sendMessage(BankingSystem* system, Task* task)
{
	char msgBuff[512]{};
	std::cout << "Enter reason for rejection>> ";
	std::cin.ignore();
	std::cin.getline(msgBuff, 512);
	MyString msg(msgBuff);

	DataPlaceholderTask* newTaskPtr = nullptr;
	if (newTaskPtr = dynamic_cast<DataPlaceholderTask*>(task))
	{
		Client& clRef = system->getClientByEGN(newTaskPtr->getEGN());
		clRef.addMessage(Message("Your request wasn't approved. Reason: " + msg));
		std::cout << std::endl;
	}

}

DisapproveTaskCommands::DisapproveTaskCommands(Banker& ref) : BankerCommands(ref)
{
}

Commands* DisapproveTaskCommands::clone() const
{
	return new DisapproveTaskCommands(*this);
}

void DisapproveTaskCommands::execute(BankingSystem* system)
{
	try
	{
		int idx = 0;

		std::cout << "Enter task idx>> ";
		std::cin >> idx;

		Task* taskPtr = _ref.getTask(idx);

		sendMessage(system, taskPtr);
		
		_ref.removeTaskAt(idx);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}
