#include "ListAccountsCommand.h"

Command* ListAccountsCommand::clone() const
{
    return new ListAccountsCommand(*this);
}

void ListAccountsCommand::execute(BankingSystem* system) const
{
    MyString bankName;
    std::cin >> bankName;

    try
    {
        system->listAccountsOfClient(bankName);
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}
