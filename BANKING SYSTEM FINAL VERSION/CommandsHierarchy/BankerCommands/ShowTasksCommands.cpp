#include "ShowTasksCommands.h"

ShowTasksCommands::ShowTasksCommands(Banker& ref) : BankerCommands(ref)
{}

Commands* ShowTasksCommands::clone() const
{
    return new ShowTasksCommands(*this);
}

void ShowTasksCommands::execute(BankingSystem* system)
{
    _ref.previewTasks();
    std::cout << std::endl;
}
