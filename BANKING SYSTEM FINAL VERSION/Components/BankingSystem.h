#pragma once
#include "../Helpers/MyString.h"
#include "../Helpers/MyVector.hpp"
#include "../Components/Bank.h"
#include "../UsersHierarchy/User.h"
#include "../UsersHierarchy/Client.h"
#include "../UsersHierarchy/Banker.h"
#include "../UsersHierarchy/ThirdPartyEmployee.h"
#include "../Components/Cheque.h"
#include "../Components/Message.h"
#include "../TasksHierarchy/Task.h"

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

	void writeToFile() const;
	void readFromFile();

	void saveClients() const;
	void saveBanks() const;
	void saveThirdParty() const;

	void loadClients();
	void loadBanks();
	void loadThirdParty();

	BankingSystem();
	~BankingSystem();

public:

	static BankingSystem& getInstance();

	BankingSystem(const BankingSystem& other) = delete;
	BankingSystem& operator=(const BankingSystem& other) = delete;

	void logIn(const MyString& EGN,  const MyString& password);
	void logOut();

	LoggedType getLoggedType() const;
	User* getLoggedUser();

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

	const Client& getClientByEGN(const MyString& EGN) const;
	Client& getClientByEGN(const MyString& EGN);

	void sendCheque(const MyString& EGN, const Cheque& Cheque, const MyString& sender);
};
