#include "WhoAmICommand.h"

void WhoAmICommand::execute(BankingSystem* system) const
{
    try
    {
        system->whoAmI();
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}

Command* WhoAmICommand::clone() const
{
    return new WhoAmICommand(*this);
}
