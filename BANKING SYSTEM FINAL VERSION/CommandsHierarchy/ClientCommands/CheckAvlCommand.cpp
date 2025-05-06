#include <iostream>
#include "CheckAvlCommand.h"

Command* CheckAvlCommand::clone() const
{
    return new CheckAvlCommand(*this);
}

void CheckAvlCommand::execute(BankingSystem* system) const
{
    MyString bankName;
    unsigned accountId = 0;

    std::cin >> bankName >> accountId;

    try
    {
        system->checkAvl(bankName, accountId);
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}
