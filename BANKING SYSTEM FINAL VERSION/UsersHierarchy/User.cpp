#include "User.h"
#include <utility>
#include <iostream>
#include <fstream>

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
	std::cout << "Name: " << _firstName << ' ' << _lastName<<std::endl;
	std::cout << "Age: " << _age << std::endl;
	std::cout << "EGN: " << _EGN << std::endl;
}

void User::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, _firstName);
	writeStringToFile(ofs, _lastName);
	writeStringToFile(ofs, _EGN);
	writeStringToFile(ofs, _password);
	ofs.write((const char*)&_age, sizeof(unsigned));
}

void User::readFromFile(std::ifstream& ifs)
{
	_firstName = readStringFromFile(ifs);
	_lastName = readStringFromFile(ifs);
	_EGN = readStringFromFile(ifs);
	_password = readStringFromFile(ifs);
	ifs.read((char*)&_age, sizeof(unsigned));
}
