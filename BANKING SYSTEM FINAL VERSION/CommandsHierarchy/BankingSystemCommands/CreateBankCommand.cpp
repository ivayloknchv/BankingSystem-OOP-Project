#include "CreateBankCommand.h"

Command* CreateBankCommand::clone() const
{
    return nullptr;
}

void CreateBankCommand::execute(BankingSystem* system)
{
    MyString bankName;
    std::cin >> bankName;

    try
    {
        system->addBank(std::move(bankName));

        std::cout << "Successfully registrated a new bank in the system!";
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}
