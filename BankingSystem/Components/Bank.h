#pragma once
#include "MyVector.hpp"
#include "Banker.h"
#include "Account.h"
#include "MyString.h"
#include "Client.h"

class Bank
{
	MyString _bankName;
	MyVector<Banker> _bankers;
	MyVector<Account> _accounts;

	size_t findLeastEmployed() const;

	size_t findBankerByEGN(const MyString& EGN) const;

	size_t internalSearchOfAccount(const Account& acc) const;
	size_t internalSearchOfAccountById(unsigned id) const;

public:

	Bank() = default;
	Bank(const MyString& bankName);
	Bank(MyString&& bankName);

	void addBanker(const Banker& banker);
	void addbanker(Banker&& banker);
	
	void addAccount(const Account& acc);
	void addAccount(Account&& acc);

	const MyString& getBankName() const;
	size_t getBankersCount() const;

	const Banker& getBankerByEGN(const MyString& EGN) const;
	const Banker& getBankerByIdx(size_t idx) const;
	Banker& getBankerByIdx(size_t idx);

	const Account& getAccountById(size_t id) const;

	void removeAccount(const Account& acc);

	void assignTask(Task* ptr);

	void previewAccountsOfClient(const Client& client) const;

	bool bankerExists(const MyString& EGN) const;

	void checkAccountBalance(unsigned id) const;

	void changeBalanceOfAccount(unsigned id, double sum);
};

