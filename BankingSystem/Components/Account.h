#pragma once
#include "MyString.h"

class Account
{
	static unsigned counter;

	unsigned _id = 0;
	MyString _firstName = "Unknown";
	MyString _lastName = "Unknown";
	MyString _EGN = "Unknown";
	unsigned _age = 0;

	MyString _bankName;
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

	friend bool operator==(const Account& lhs, const Account& rhs);
	friend bool operator!=(const Account& lhs, const Account& rhs);
};

