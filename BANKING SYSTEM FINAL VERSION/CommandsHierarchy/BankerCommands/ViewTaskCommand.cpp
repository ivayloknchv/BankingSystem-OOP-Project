#include "ViewTaskCommand.h"

Command* ViewTaskCommand::clone() const
{
	return new ViewTaskCommand(*this);
}

void ViewTaskCommand::execute(BankingSystem* system)
{
	size_t taskIdx = 0;
	std::cin >> taskIdx;
	try
	{
		system->viewTask(taskIdx);
	}

	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
