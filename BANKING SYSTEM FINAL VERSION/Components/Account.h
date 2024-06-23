#pragma once
#include <fstream>
#include "../Helpers/MyString.h"

class Account
{
	static unsigned counter;

	unsigned _id = 0;
	MyString _firstName = "Unknown";
	MyString _lastName = "Unknown";
	MyString _EGN = "Unknown";
	unsigned _age = 0;
	MyString _bankName = "Unknown";
	double _balance = 0.00;

public:

	Account() = default;

	Account(const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age, const MyString& bankName);

	Account(MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age, MyString&& bankName);

	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getEGN() const;
	const MyString& getBankName() const;
	unsigned getAge() const;
	unsigned getId() const;
	double getBalance() const;

	void addBalance(double amount);

	void printAccount() const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};

