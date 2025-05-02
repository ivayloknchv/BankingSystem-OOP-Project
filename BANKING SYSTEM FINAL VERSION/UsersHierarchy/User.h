#pragma once
#include "../Helpers/MyString.h"
#include "../Helpers/HelperFuncs.h"

class User
{
protected:

	MyString _firstName = "Unknown";
	MyString _lastName = "Unknown";
	MyString _EGN = "Unknown";
	MyString _password = "Unknown";
	unsigned _age = 0;

public:

	User() = default;
	User(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age);
	User(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age);

	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getEGN() const;
	unsigned getAge() const;

	bool isValidPassword(const MyString& password) const;
	virtual void whoAmI() const = 0;
	virtual void help() const = 0;
	virtual User* clone() const = 0;
	virtual ~User() = default;

	virtual void writeToFile(std::ofstream& ofs) const = 0;
	virtual void readFromFile(std::ifstream& ifs) = 0;
};

