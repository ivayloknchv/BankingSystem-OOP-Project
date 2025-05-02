#pragma once
#include "../Helpers/MyVector.hpp"
#include "../UsersHierarchy/Banker.h"
#include "../Components/Account.h"
#include "../Helpers/MyString.h"
#include "../UsersHierarchy/Client.h"

class Bank
{
	MyString _bankName;
	MyVector<Banker> _bankers;
	MyVector<Account> _accounts;

	size_t findLeastEmployed() const;
	size_t findBankerByEGN(const MyString& EGN) const;
	size_t findAccountById(unsigned id) const;

public:

	Bank() = default;
	Bank(const MyString& bankName);
	Bank(MyString&& bankName);

	void addBanker(const Banker& banker);
	void addBanker(Banker&& banker);
	
	void addAccount(const Account& acc);
	void addAccount(Account&& acc);

	void assignTask(Task* ptr);
	void assignTask(const polymorphic_ptr<Task>& task);

	const MyString& getBankName() const;
	size_t getBankersCount() const;

	bool bankerExists(const MyString& EGN) const;
	const Banker& getBankerByEGN(const MyString& EGN) const;
	const Banker& getBankerByIdx(size_t idx) const;
	Banker& getBankerByIdx(size_t idx);

	const Account& getAccountById(size_t id) const;
	void removeAccountByID(size_t id);

	bool accountExists(unsigned accId) const;

	void previewAccountsOfClient(const MyString& clientEGN) const;
	void changeBalanceOfAccount(unsigned id, const MyString& EGN, double sum);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};

