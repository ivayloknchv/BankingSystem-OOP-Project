#include "ChangeBankCommand.h"
#include "../../TasksHierarchy/ChangeBankTask.h"

Command* ChangeBankCommand::clone() const
{
    return new ChangeBankCommand(*this);
}

void ChangeBankCommand::execute(BankingSystem* system) const
{
    MyString newBank, currentBank;
    unsigned accountId;

    std::cout << "Enter new bank name>> ";
    std::cin >> newBank >> currentBank >> accountId;

    try
    {
        system->changeBank(newBank, currentBank, accountId);
        std::cout << "Successfully sent a request for moving to another bank!";
    }

    catch(std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}


