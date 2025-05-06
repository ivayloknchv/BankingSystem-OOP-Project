#include "ShowTasksCommand.h"

Command* ShowTasksCommand::clone() const
{
    return new ShowTasksCommand(*this);
}

void ShowTasksCommand::execute(BankingSystem* system) const
{
    try
    {
        system->viewTasks();
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}
