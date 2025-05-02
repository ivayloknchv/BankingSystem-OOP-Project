#include "CreateBankCommands.h"

Commands* CreateBankCommands::clone() const
{
    return nullptr;
}

void CreateBankCommands::execute(BankingSystem* system)
{
    try
    {
        MyString name;
        std::cout << "Enter bank name: ";
        std::cin >> name;

        system->addBank(std::move(name));

        std::cout << "Successfully registrated a new bank in the system!" << std::endl<<std::endl;
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl << std::endl;
    }
}
