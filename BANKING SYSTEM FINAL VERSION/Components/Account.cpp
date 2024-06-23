#include "Account.h"
#include "../Helpers/HelperFuncs.h"
#include <utility>
#include <iostream>

unsigned Account::counter = 100;

Account::Account(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& bankName):
_firstName(firstName), _lastName(lastName), _EGN(EGN), _age(age), _bankName(bankName)
{
	_id = counter;
	counter++;
}

Account::Account(MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age, MyString&& bankName):
	_firstName(std::move(firstName)), _lastName(std::move(lastName)), _EGN(std::move(EGN)), _age(age), _bankName(std::move(bankName))
{
	_id = counter;
	counter++;
}

const MyString& Account::getFirstName() const
{
	return _firstName;
}

const MyString& Account::getLastName() const
{
	return _lastName;
}

const MyString& Account::getEGN() const
{
	return _EGN;
}

unsigned Account::getAge() const
{
	return _age;
}

double Account::getBalance() const
{
	return _balance;
}

void Account::addBalance(double amount)
{
	_balance += amount;
}

const MyString& Account::getBankName() const
{
	return _bankName;
}

unsigned Account::getId() const
{
	return _id;
}

void Account::printAccount() const
{
	std::cout << _id << ' ' << _bankName << ' ' << _balance <<'$' << std::endl;
}

void Account::writeToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&counter, sizeof(unsigned));
	ofs.write((const char*)&_id, sizeof(unsigned));
	writeStringToFile(ofs, _firstName);
	writeStringToFile(ofs, _lastName);
	writeStringToFile(ofs, _EGN);
	ofs.write((const char*)&_age, sizeof(unsigned));
	writeStringToFile(ofs, _bankName);
	ofs.write((const char*)&_balance, sizeof(double));
}

void Account::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)&counter, sizeof(unsigned));
	ifs.read((char*)&_id, sizeof(unsigned));
	_firstName = readStringFromFile(ifs);
	_lastName = readStringFromFile(ifs);
	_EGN = readStringFromFile(ifs);
	ifs.read((char*)&_age, sizeof(unsigned));
	_bankName = readStringFromFile(ifs);
	ifs.read((char*)&_balance, sizeof(double));
}
