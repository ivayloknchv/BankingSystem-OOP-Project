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


class BankingSystem
{
	struct LoggedInData
	{
		User* logged = nullptr;
		Client* loggedClient = nullptr;
		Banker* loggedBanker = nullptr;
		ThirdPartyEmployee* loggedThirdParty = nullptr;
		UserType type = UserType::Unknown;
	};

	LoggedInData loggedData;

	MyVector<polymorphic_ptr<User>> _users;
	MyVector<Bank> _banks;

	bool userExists(const User* user) const;
	size_t findUserByEGN(const MyString& EGN) const;
	size_t findBankByName(const MyString& name) const;

	void writeToFile() const;
	void readFromFile();

	void saveUsers() const;
	void saveBanks() const;

	void loadUsers();
	void loadBanks();

	BankingSystem();
	~BankingSystem();

public:

	static BankingSystem& getInstance();

	BankingSystem(const BankingSystem& other) = delete;
	BankingSystem& operator=(const BankingSystem& other) = delete;

	void addBank(const Bank& bank);
	void addBank(Bank&& bank);

	void addClient(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age);
	void addClient(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age);

	void addBanker(const MyString& firstName, const MyString& lastName, const MyString& EGN, 
		const MyString& password, unsigned age, const MyString& bankName);
	void addClient(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age, MyString&& bankName);

	void addThirdPartyEmployee(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age);
	void addThirdPartyEmployee(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age);

	size_t getBanksCount() const;

	const Bank& getBankByName(const MyString& name) const;
	Bank& getBankByName(const MyString& name);

	void sendMessage(const MyString& clientEGN, const Message& message);
	void sendMessage(const MyString& clientEGN, Message&& message);

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
