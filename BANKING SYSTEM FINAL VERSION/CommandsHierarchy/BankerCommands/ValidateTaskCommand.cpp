#include "ValidateTaskCommand.h"

Command* ValidateTaskCommand::clone() const
{
	return new ValidateTaskCommand(*this);
}

void ValidateTaskCommand::execute(BankingSystem* system) const
{
	unsigned taskIdx;
	std::cin >> taskIdx;
	
	try
	{
		system->validateTask(taskIdx);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
