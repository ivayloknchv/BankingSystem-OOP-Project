#include "ListAccountsCommands.h"

ListAccountsCommands::ListAccountsCommands(Client& ref) : ClientCommands(ref)
{}

Commands* ListAccountsCommands::clone() const
{
    return new ListAccountsCommands(*this);
}

void ListAccountsCommands::execute(BankingSystem* system)
{
    try
    {
        MyString name;
        std::cout << "Enter bank name>> ";
        std::cin >> name;
        std::cout << std::endl;

        system->getBankByName(name).previewAccountsOfClient(_ref);
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl << std::endl;
    }
}
