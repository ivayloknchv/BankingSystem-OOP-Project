#include "ViewTaskCommands.h"

ViewTaskCommands::ViewTaskCommands(Banker& ref) : BankerCommands(ref)
{}

Commands* ViewTaskCommands::clone() const
{
	return new ViewTaskCommands(*this);
}

void ViewTaskCommands::execute(BankingSystem* system)
{
	try
	{
		size_t idx = 0;

		std::cout << "Enter task idx>> ";
		std::cin >> idx;

		_ref.viewTask(idx);
		std::cout << std::endl;
	}

	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}
