#include "ExitCommand.h"

void ExitCommand::execute(BankingSystem* system)
{
    try
    {
        system->exit();
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}

Command* ExitCommand::clone() const
{
    return new ExitCommand(*this);
}
