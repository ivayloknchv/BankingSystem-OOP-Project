#include "LogInCommands.h"

Commands* LogInCommands::clone() const
{
    return new LogInCommands(*this);
}

void LogInCommands::execute(BankingSystem* system)
{
    try
    {
        MyString firstName, lastName, password;

        std::cout << "Enter first name>> ";
        std::cin >> firstName;

        std::cout << "Enter last name>> ";
        std::cin >> lastName;

        std::cout << "Enter password>> ";
        std::cin >> password;

        system->logIn(firstName, lastName, password);

        std::cout << std::endl;
        std::cout << "Successfully logged into the system!" << std::endl << std::endl;
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}
