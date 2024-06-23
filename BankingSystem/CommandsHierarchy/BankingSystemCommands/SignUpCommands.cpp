#include "SignUpCommands.h"

static void userInput(MyString& firstName, MyString& lastName, MyString& EGN, unsigned& age, MyString& password)
{

    std::cout << "Enter first name>> ";
    std::cin >> firstName;

    std::cout << "Enter last name>> ";
    std::cin >> lastName;

    std::cout << "Enter EGN>> ";
    std::cin >> EGN;

    std::cout << "Enter age>> ";
    std::cin >> age;

    std::cout << "Enter password>> ";
    std::cin >> password;
}

void SignUpCommands::registerClient(BankingSystem* system)
{
    try
    {
        MyString firstName;
        MyString lastName;
        MyString EGN;
        unsigned age = 0;
        MyString password;

        userInput(firstName, lastName, EGN, age, password);

        system->addClient(Client(firstName, lastName, EGN, password, age));

       
        std::cout << "\nSuccessfully registrated a new client in the system!\n\n";
    }

    catch(std::invalid_argument& e)
    {
        std::cout<<e.what() << std::endl;
    }
}

void SignUpCommands::registerBanker(BankingSystem* system)
{
    try
    {
        if (system->getBanksCount() == 0)
        {
            throw std::invalid_argument("No banks registrated!");
        }

        MyString firstName;
        MyString lastName;
        MyString EGN;
        unsigned age = 0;
        MyString password;
        MyString bankName;

        userInput(firstName, lastName, EGN, age, password);

        std::cout << "Enter bank name>> ";
        std::cin >> bankName;

        system->addBanker(Banker(firstName, lastName, EGN, password, age), bankName);

        std::cout << "\nSuccessfully registrated a new banker in the system!\n\n";
    }

    catch(std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void SignUpCommands::registerThirdParty(BankingSystem* system)
{
    try
    {
        MyString firstName;
        MyString lastName;
        MyString EGN;
        unsigned age = 0;
        MyString password;

        userInput(firstName, lastName, EGN, age, password);

        system->addThirdPartyEmployee(ThirdPartyEmployee(firstName, lastName, EGN, password, age));

        std::cout << "\nSuccessfully registrated a new third-party employee in the system!\n\n";
    }

    catch (std::invalid_argument& e)
    {
        std::cout<<e.what()<<std::endl;
    }
}

Commands* SignUpCommands::clone() const
{
    return new SignUpCommands(*this);
}

void SignUpCommands::execute(BankingSystem* system)
{
    std::cout << "Sign up as: "<<std::endl;
    std::cout << "1) Client" << std::endl;
    std::cout << "2) Banker" << std::endl;
    std::cout << "3) Third party employee" << std::endl << std::endl;

    int option = 0;

    std::cout << "Enter your option>> ";
    std::cin >> option;
    std::cout << std::endl;

    switch (option)
    {

    case 1:

        registerClient(system);
        break;

    case 2: 

        registerBanker(system);
        break;

    case 3: 
        
        registerThirdParty(system);
        break;

    default: 

        std::cout << "Invalid command!" << std::endl << std::endl;
        break;
    }
}
