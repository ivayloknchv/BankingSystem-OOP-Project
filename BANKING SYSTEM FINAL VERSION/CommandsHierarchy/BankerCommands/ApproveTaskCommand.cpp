#include "ApproveTaskCommand.h"

Command* ApproveTaskCommand::clone() const
{
	return new ApproveTaskCommand(*this);
}

void ApproveTaskCommand::execute(BankingSystem* system) const
{
	size_t idx = 0;
	std::cin >> idx;

	try
	{
		system->approveTask(idx);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
