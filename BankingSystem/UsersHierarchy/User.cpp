#include "User.h"
#include <utility>
#include <iostream>

User::User(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age) :
	_firstName(firstName), _lastName(lastName), _EGN(EGN), _password(password), _age(age)
{
}

User::User(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age):
	_firstName(std::move(firstName)), _lastName(std::move(lastName)), _EGN(std::move(EGN)), _password(std::move(password)), _age(age)
{
}

const MyString& User::getFirstName() const
{
	return _firstName;
}

const MyString& User::getLastName() const
{
	return _lastName;
}

const MyString& User::getEGN() const
{
	return _EGN;
}

unsigned User::getAge() const
{
	return _age;
}

bool User::isValidPassword(const MyString& password) const
{
	return _password == password;
}

void User::whoAmI() const
{
	std::cout << "Name: " << _firstName << ' ' << _lastName;
	std::cout << "Age: " << _age << std::endl;
	std::cout << "EGN: " << _EGN << std::endl;
}
