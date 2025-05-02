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

	// common user interface
	void whoAmI() const;
	void help() const;
	void logIn(const MyString& EGN, const MyString& password);
	void exit();

	// client commands
	void checkAvl(const MyString& bankName, unsigned accountID) const;
	void openAccount(const MyString& bankName);
	void closeAccount(const MyString& bankName, unsigned accountID);
	void redeemCheque(const MyString& bankName, unsigned accountID, const MyString& code);
	void changeBank(const MyString& newBankName, const MyString& currentBankName, unsigned accountID);
	void listAccountsOfClient(const MyString& bankName);
	void viewMessages() const;

	//banker commands
	void viewTasks() const;
	void viewTask(unsigned taskIdx) const;
	void approveTask(unsigned taskIdx);
	void disapproveTask(unsigned taskIdx);
	void validateTask(unsigned taskIdx);

	//third party employees commands
	void sendCheque(double sum, const MyString& code, const MyString& EGN);
};
