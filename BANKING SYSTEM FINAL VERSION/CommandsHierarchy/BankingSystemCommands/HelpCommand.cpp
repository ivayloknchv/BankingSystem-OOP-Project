#include "HelpCommand.h"

void HelpCommand::execute(BankingSystem* system)
{
    try
    {
        system->help();
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}

Command* HelpCommand::clone() const
{
    return new HelpCommand(*this);
}
