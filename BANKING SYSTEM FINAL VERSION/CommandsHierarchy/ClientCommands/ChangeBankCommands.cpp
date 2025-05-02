#include "ChangeBankCommands.h"
#include "../../TasksHierarchy/ChangeBankTask.h"

ChangeBankCommands::ChangeBankCommands(Client& ref) :  ClientCommands(ref)
{}

Commands* ChangeBankCommands::clone() const
{
    return new ChangeBankCommands(*this);
}

void ChangeBankCommands::execute(BankingSystem* system)
{
    MyString newBank, currentBank;
    unsigned id;

    std::cout << "Enter new bank name>> ";
    std::cin >> newBank;
    std::cout << "Enter current bank name>> ";
    std::cin >> currentBank;
    std::cout << "Enter account id>> ";
    std::cin >> id;

    try
    {
        const Bank& bankRef=system->getBankByName(currentBank);
        const Account& accRef = bankRef.getAccountById(id);

        if (accRef.getEGN() != _ref.getEGN())
        {
            throw std::invalid_argument("This isn't the owner of the account!");
        }

        polymorphic_ptr<Task> task = new ChangeBankTask(accRef.getFirstName(), accRef.getLastName(), 
            accRef.getEGN(), accRef.getAge(), currentBank, accRef.getId(), accRef.getBalance(), newBank);

        system->assignTaskToBank(newBank, task);

       std::cout << "Successfully sent a request for moving to another bank!" << std::endl << std::endl;
    }

    catch(std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl<<std::endl;
    }
}
