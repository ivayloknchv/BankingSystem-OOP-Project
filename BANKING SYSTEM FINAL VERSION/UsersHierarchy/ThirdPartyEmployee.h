#pragma once
#include "User.h"

class ThirdPartyEmployee : public User
{
public:

	ThirdPartyEmployee() = default;

	ThirdPartyEmployee(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age);
	ThirdPartyEmployee(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age);

	User* clone() const override;

	void whoAmI() const override;

	void writeToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};

