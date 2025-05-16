#include "ThirdPartyEmployee.h"
#include <utility>

ThirdPartyEmployee::ThirdPartyEmployee(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age)
	:User(firstName, lastName, EGN, password, age)
{}

ThirdPartyEmployee::ThirdPartyEmployee(MyString && firstName, MyString && lastName, MyString && EGN, MyString && password, unsigned age)
	:User(std::move(firstName), std::move(lastName), std::move(EGN), std::move(password),age)
{}

User* ThirdPartyEmployee::clone() const
{
	return new ThirdPartyEmployee(*this);
}

void ThirdPartyEmployee::whoAmI() const
{
	User::whoAmI();
	std::cout << "Status: Third-party employee" << std::endl;
}

void ThirdPartyEmployee::writeToFile(std::ofstream& ofs) const
{
	UserType tp = UserType::ThirdParty;
	ofs.write((const char*)&tp, sizeof(tp));
	User::writeToFile(ofs);
}

void ThirdPartyEmployee::readFromFile(std::ifstream& ifs)
{
	User::readFromFile(ifs);
}

void ThirdPartyEmployee::help() const
{
	std::cout << "send_cheque [sum] [egn] [verification_code]" << std::endl;
}
