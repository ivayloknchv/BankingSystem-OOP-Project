#include "LogInCommand.h"

Command* LogInCommand::clone() const
{
    return new LogInCommand(*this);
}

void LogInCommand::execute(BankingSystem* system)
{
    try
    {
        MyString EGN, password;
        std::cin >> EGN >> password;
        system->logIn(EGN, password);
        std::cout << "Successfully logged into the system!";
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}
