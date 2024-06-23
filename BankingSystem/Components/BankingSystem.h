#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Bank.h"
#include "User.h"
#include "Client.h"
#include "Banker.h"
#include "ThirdPartyEmployee.h"
#include "Cheque.h"
#include "Message.h"
#include "Task.h"

enum class LoggedType
{
	Unknown, 
	Client,
	Banker,
	ThirdParty
};

class BankingSystem
{
	struct loggedInData
	{
		User* logged = nullptr;
		LoggedType type = LoggedType::Unknown;
	};

	loggedInData loggedData;

	MyVector<Bank> _banks;
	MyVector<Client> _clients;
	MyVector<ThirdPartyEmployee> _thirdParty;

	bool userExists(const User* user) const;
	size_t findBankByName(const MyString& name) const;
	size_t findClientByEGN(const MyString& EGN) const;
	size_t findThirdPartyByEGN(const MyString& EGN) const;

public:

	void logIn(const MyString& firstName, const MyString& lastName, const MyString& password);
	void logOut();

	void addBank(const Bank& bank);
	void addBank(Bank&& bank);

	void addClient(const Client& client);
	void addClient(Client&& client);

	void addBanker(const Banker& banker, const MyString& bankName);
	void addBanker(Banker&& banker, MyString&& bankName);

	void addThirdPartyEmployee(const ThirdPartyEmployee& thirdParty);
	void addThirdPartyEmployee(ThirdPartyEmployee&& thirdParty);

	size_t getBanksCount() const;

	const Bank& getBankByName(const MyString& name) const;
	Bank& getBankByName(const MyString& name);
};

