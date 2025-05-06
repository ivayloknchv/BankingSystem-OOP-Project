#include "DisapproveTaskCommand.h"

Command* DisapproveTaskCommand::clone() const
{
	return new DisapproveTaskCommand(*this);
}

void DisapproveTaskCommand::execute(BankingSystem* system) const
{
	unsigned taskIdx = 0;
	std::cin >> taskIdx;

	try
	{
		system->disapproveTask(taskIdx);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
