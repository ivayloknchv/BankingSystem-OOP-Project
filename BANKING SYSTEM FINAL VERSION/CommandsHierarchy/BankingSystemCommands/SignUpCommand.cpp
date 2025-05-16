#include "SignUpCommand.h"

static bool isValidEGN(const MyString& string)
{
    if (string.getSize() != 10)
    {
        return false;
    }

    return stringHasDigitsOnly(string.c_str());
}

static bool isValidName(const MyString& string)
{
    return isCapitalLetter(string[0]) && hasSmallLetersOnly(string.c_str() + 1);
}

static bool validateUserData(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age)
{
    if (!isValidName(firstName))
    {
        throw std::invalid_argument("First name isn't correctly formatted!");
    }
    if (!isValidName(lastName))
    {
        throw std::invalid_argument("Last name isn't correctly formatted!");
    }
    if (!isValidEGN(EGN))
    {
        throw std::invalid_argument("EGN isn't correctly formatted!");
    }
    if (!isValidAge(age))
    {
        throw std::invalid_argument("Users under 18 years old cannot open a bank account!");
    }

    return true;
}

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

void SignUpCommand::registerClient(BankingSystem* system) const
{
    try
    {
        MyString firstName;
        MyString lastName;
        MyString EGN;
        unsigned age = 0;
        MyString password;

        userInput(firstName, lastName, EGN, age, password);

        
        if (validateUserData(firstName, lastName, EGN, age))
        {
            system->addClient(firstName, lastName, EGN, password, age);
            std::cout << "Successfully registrated a new client in the system!";
        }
    }

    catch(std::invalid_argument& e)
    {
        std::cout << e.what();
    }
}

void SignUpCommand::registerBanker(BankingSystem* system) const
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

        if (validateUserData(firstName, lastName, EGN, age))
        {
            system->addBanker(firstName, lastName, EGN, password, age, bankName);
            std::cout << "Successfully registrated a new banker in the system!" << std::endl << std::endl;
        }

       
    }

    catch(std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl<<std::endl;
    }
}

void SignUpCommand::registerThirdParty(BankingSystem* system) const
{
    try
    {
        MyString firstName;
        MyString lastName;
        MyString EGN;
        unsigned age = 0;
        MyString password;

        userInput(firstName, lastName, EGN, age, password);

        if (validateUserData(firstName, lastName, EGN, age))
        {
            system->addThirdPartyEmployee(firstName, lastName, EGN, password, age);
            std::cout << "Successfully registrated a new third-party employee in the system!" << std::endl << std::endl;
        }       
    }

    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl << std::endl;
    }
}

Command* SignUpCommand::clone() const
{
    return new SignUpCommand(*this);
}

void SignUpCommand::execute(BankingSystem* system) const
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
