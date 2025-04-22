#include "LogInCommands.h"

Commands* LogInCommands::clone() const
{
    return new LogInCommands(*this);
}

void LogInCommands::execute(BankingSystem* system)
{
    try
    {
        MyString EGN, password;

        std::cout << "Enter EGN>> ";
        std::cin >> EGN;

        std::cout << "Enter password>> ";
        std::cin >> password;

        system->logIn(EGN, password);

        std::cout << std::endl;
        std::cout << "Successfully logged into the system!" << std::endl << std::endl;
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl<<std::endl;
    }
}
