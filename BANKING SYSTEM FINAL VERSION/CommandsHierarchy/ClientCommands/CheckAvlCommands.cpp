#include "CheckAvlCommands.h"

CheckAvlCommands::CheckAvlCommands(Client& ref) : ClientCommands(ref)
{
}

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
        const Account& accRef = system->getBankByName(name).getAccountById(id);
        
        if (accRef.getEGN() != _ref.getEGN())
        {
            throw std::invalid_argument("You are not the owner of this bank account!");
        }

        accRef.printAccount();
        std::cout << std::endl;
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl<<std::endl;
    }
}
