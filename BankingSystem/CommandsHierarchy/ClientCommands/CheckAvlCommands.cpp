#include "CheckAvlCommands.h"

Commands* CheckAvlCommands::clone() const
{
    return new CheckAvlCommands(*this);
}

void CheckAvlCommands::execute(BankingSystem* system)
{
    MyString name;
    int id = 0;

    std::cout << "Enter bank name>> ";
    std::cin >> name;

    std::cout << "Enter account ID>> ";
    std::cin >> id;

    try
    {
        system->getBankByName(name).checkAccountBalance(id);
        std::cout << std::endl;
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl<<std::endl;
    }
}
