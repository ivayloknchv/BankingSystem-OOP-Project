#include "BankingSystem.h"
#include <stdexcept>
#include <utility>
#include "../TasksHierarchy/OpenAccountTask.h"
#include "../TasksHierarchy/CloseAccountTask.h"
#include "../TasksHierarchy/ChangeBankTask.h"
#include "../UsersHierarchy/UserFactory.h"

static bool isLogInDataValid(const MyString& EGN, const MyString& password, const User* user)
{
	if (!user)
	{
		return false;
	}

	return (user->getEGN() == EGN && user->isValidPassword(password));
}

bool BankingSystem::userExists(const User* user) const
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (user->getEGN() == _users[i]->getEGN())
		{
			return true;
		}
	}
	return false;
}

size_t BankingSystem::findUserByEGN(const MyString& EGN) const
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (_users[i]->getEGN()==EGN)
		{
			return i;
		}
	}
	return _users.size();
}

size_t BankingSystem::findBankByName(const MyString& name) const
{
	size_t size = _banks.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_banks[i].getBankName() == name)
		{
			return i;
		}
	}

	return size;
}

void BankingSystem::saveUsers() const
{
	std::ofstream ofs("users.dat", std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}
	size_t size = _users.size();
	ofs.write((const char*)&(size), sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		_users[i]->writeToFile(ofs);
	}

	ofs.close();
}

void BankingSystem::saveBanks() const
{
	std::ofstream ofs("banks.dat", std::ios::binary);
	if (!ofs.is_open())
	{
		return;
	}

	size_t banksCount = _banks.size();
	ofs.write((const char*)&banksCount, sizeof(size_t));

	for (size_t i = 0; i < banksCount; i++)
	{
		_banks[i].writeToFile(ofs);
	}

	ofs.close();
}

void BankingSystem::loadUsers()
{
	std::ifstream ifs("users.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t size = 0;
	ifs.read((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		_users.push_back(UserFactory::createUser(ifs));
	}

	ifs.close();
}

void BankingSystem::loadBanks()
{
	std::ifstream ifs("banks.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t banksCount = 0;

	ifs.read((char*)&banksCount, sizeof(size_t));

	for (size_t i = 0; i < banksCount; i++)
	{
		Bank temp;
		temp.readFromFile(ifs, _users);
		_banks.push_back(std::move(temp));
	}

	ifs.close();
}

BankingSystem::BankingSystem()
{
	readFromFile();
}

BankingSystem::~BankingSystem()
{
	writeToFile();
}

void BankingSystem::addBank(const Bank& bank)
{
	if (findBankByName(bank.getBankName()) != _banks.size())
	{
		throw std::invalid_argument("Bank with this name is already registrated!");
	}

	_banks.push_back(bank);
}

void BankingSystem::addBank(Bank&& bank)
{
	if (findBankByName(bank.getBankName()) != _banks.size())
	{
		throw std::invalid_argument("Bank with this name is already registrated!");
	}

	_banks.push_back(std::move(bank));
}

void BankingSystem::addClient(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age)
{
	User* client = new Client(firstName, lastName, EGN, password, age);
	_users.push_back(client);
}

void BankingSystem::addClient(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age)
{
	User* client = new Client(std::move(firstName), std::move(lastName), std::move(EGN), std::move(password), age);
	_users.push_back(client);
}

void BankingSystem::addBanker(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age, const MyString& bankName)
{
	size_t bankIdx = findBankByName(bankName);

	if (bankIdx == _banks.size())
	{
		throw std::invalid_argument("Bank doesn't exist!");
	}

	Banker* banker = new Banker(firstName, lastName, EGN, password, age, bankName);
	_banks[bankIdx].addBanker(banker);
	_users.push_back(banker);
}

void BankingSystem::addClient(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age, MyString&& bankName)
{
	size_t bankIdx = findBankByName(bankName);

	if (bankIdx == _banks.size())
	{
		throw std::invalid_argument("Bank doesn't exist!");
	}

	Banker* banker = new Banker(std::move(firstName), std::move(lastName), std::move(EGN), std::move(password), age, std::move(bankName));
	_banks[bankIdx].addBanker(banker);
	_users.push_back(banker);
}

void BankingSystem::addThirdPartyEmployee(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age)
{
	User* thirdParty = new ThirdPartyEmployee(firstName, lastName, EGN, password, age);
	_users.push_back(thirdParty);
}

void BankingSystem::addThirdPartyEmployee(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age)
{
	User* thirdParty = new ThirdPartyEmployee(std::move(firstName), std::move(lastName), std::move(EGN), std::move(password), age);
	_users.push_back(thirdParty);
}

size_t BankingSystem::getBanksCount() const
{
	return _banks.size();
}

const Bank& BankingSystem::getBankByName(const MyString& name) const
{
	size_t idx = findBankByName(name);

	if (idx == _banks.size())
	{
		throw std::invalid_argument("Bank with this name doesn't exist in the system!");
	}

	return _banks[idx];
}

BankingSystem& BankingSystem::getInstance()
{
	static BankingSystem instance;
	return instance;
}

void BankingSystem::whoAmI() const
{
	if (!loggedData.logged)
	{
		throw std::invalid_argument("No user is logged in!");
	}

	loggedData.logged->whoAmI();
}

void BankingSystem::help() const
{
	if (!loggedData.logged)
	{
		std::cout << "login [egn] [password]" << std::endl;
		std::cout << "signup" << std::endl;
		std::cout << "create_bank [bank_name]" << std::endl;
		std::cout << "whoami" << std::endl;
		std::cout << "help" << std::endl;
		std::cout << "exit" << std::endl;
	}
	else
	{
		loggedData.logged->help();
	}
}

void BankingSystem::logIn(const MyString& EGN, const MyString& password)
{
	if (loggedData.logged)
	{
		throw std::invalid_argument("Someone's logged in!");
	}

	for (size_t i = 0; i < _users.size(); i++)
	{
		if (isLogInDataValid(EGN, password, _users[i].get()))
		{
			loggedData.logged = _users[i].get();
			if (loggedData.loggedBanker = dynamic_cast<Banker*>(_users[i].get()))
			{
				loggedData.type = UserType::Banker;
			}
			else if (loggedData.loggedClient = dynamic_cast<Client*>(_users[i].get()))
			{
				loggedData.type = UserType::Client;
			}
			else if(loggedData.loggedThirdParty = dynamic_cast<ThirdPartyEmployee*>(_users[i].get()))
			{
				loggedData.type = UserType::ThirdParty;
			}
			return;
		}
	}
	throw std::invalid_argument("User with these data details doesn't exist!");
}

void BankingSystem::exit()
{
	loggedData = LoggedInData();
}

Bank& BankingSystem::getBankByName(const MyString& name)
{
	size_t idx = findBankByName(name);

	if (idx == _banks.size())
	{
		throw std::invalid_argument("Bank with this name doesn't exist in the system!");
	}

	return _banks[idx];
}

void BankingSystem::sendMessage(const MyString& clientEGN, const Message& message)
{
	size_t idx = findUserByEGN(clientEGN);

	if (idx == _users.size())
	{
		throw std::invalid_argument("User with such EGN doesn't exist!");
	}

	Client* clientPtr = dynamic_cast<Client*>(_users[idx].get());

	if (!clientPtr)
	{
		throw std::invalid_argument("User with such EGN isn't client!");
	}

	clientPtr->addMessage(message);
}

void BankingSystem::sendMessage(const MyString& clientEGN, Message&& message)
{
	size_t idx = findUserByEGN(clientEGN);

	if (idx == _users.size())
	{
		throw std::invalid_argument("User with such EGN doesn't exist!");
	}

	Client* clientPtr = dynamic_cast<Client*>(_users[idx].get());

	if (!clientPtr)
	{
		throw std::invalid_argument("User with such EGN isn't client!");
	}

	clientPtr->addMessage(std::move(message));
}

void BankingSystem::checkAvl(const MyString& bankName, unsigned accountID) const
{
	if (!loggedData.loggedClient || loggedData.type!=UserType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	const Account& account = getBankByName(bankName).getAccountById(accountID);

	if (account.getEGN() != loggedData.loggedClient->getEGN())
	{
		throw std::invalid_argument("Trying to access someone else's account!");
	}

	account.printAccount();
}

void BankingSystem::openAccount(const MyString& bankName)
{
	if (!loggedData.loggedClient || loggedData.type != UserType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	Bank& bank = getBankByName(bankName);

	bank.assignTask(new OpenAccountTask(loggedData.logged->getFirstName(), loggedData.logged->getLastName(),
		loggedData.logged->getEGN(), loggedData.logged->getAge(), bankName));
}

void BankingSystem::closeAccount(const MyString& bankName, unsigned accountID)
{
	if (!loggedData.loggedClient || loggedData.type != UserType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	Bank& bank = getBankByName(bankName);

	const Account& account = bank.getAccountById(accountID);

	if (account.getEGN() != loggedData.logged->getEGN())
	{
		throw std::exception("Trying to access someone else's account!");
	}

	bank.assignTask(new CloseAccountTask(account.getFirstName(), account.getLastName(), account.getEGN(),
		account.getAge(), bankName, account.getId(), account.getBalance()));
}

void BankingSystem::redeemCheque(const MyString& bankName, unsigned accountID, const MyString& code)
{
	if (!loggedData.loggedClient || loggedData.type != UserType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	Bank& bank = getBankByName(bankName);
	Client* client = loggedData.loggedClient;
	const Cheque& cheque = client->getCheque(code);
	bank.changeBalanceOfAccount(accountID, loggedData.logged->getEGN(), cheque.getSum());
	client->removeCheque(code);

}

void BankingSystem::changeBank(const MyString& newBankName, const MyString& currentBankName, unsigned accountID)
{
	if (!loggedData.loggedClient || loggedData.type != UserType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	if (newBankName == currentBankName)
	{
		throw std::invalid_argument("New bank is current bank!");
	}

	Bank& newBank = getBankByName(newBankName);
	const Bank& currentBank = getBankByName(currentBankName);
	const Account& account = currentBank.getAccountById(accountID);

	if (account.getEGN() != loggedData.logged->getEGN())
	{
		throw std::invalid_argument("Trying to access someone else's account!");
	}
	const User* user = loggedData.logged;
	newBank.assignTask(new ChangeBankTask(user->getFirstName(),user->getLastName(), user->getEGN(), user->getAge(), currentBankName,
		accountID, account.getBalance(), newBankName));
}

void BankingSystem::listAccountsOfClient(const MyString& bankName)
{
	if (!loggedData.loggedClient || loggedData.type != UserType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	getBankByName(bankName).previewAccountsOfClient(loggedData.logged->getEGN());
}

void BankingSystem::viewMessages() const
{
	if (!loggedData.loggedClient || loggedData.type != UserType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	loggedData.loggedClient->listMessages();
}

void BankingSystem::viewTasks() const
{
	if (!loggedData.loggedBanker || loggedData.type != UserType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}

	loggedData.loggedBanker->previewTasks();
}

void BankingSystem::viewTask(unsigned taskIdx) const
{
	if (!loggedData.loggedBanker || loggedData.type != UserType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}
	loggedData.loggedBanker->viewTask(taskIdx);
}

void BankingSystem::approveTask(unsigned taskIdx)
{
	if (!loggedData.loggedBanker || loggedData.type != UserType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}
	loggedData.loggedBanker->approveTask(taskIdx);
}

void BankingSystem::disapproveTask(unsigned taskIdx)
{
	if (!loggedData.loggedBanker || loggedData.type != UserType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}
	loggedData.loggedBanker->disapproveTask(taskIdx);
}

void BankingSystem::validateTask(unsigned taskIdx)
{
	if (!loggedData.loggedBanker || loggedData.type != UserType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}
	loggedData.loggedBanker->validateTask(taskIdx);
}

void BankingSystem::sendCheque(double sum, const MyString& code, const MyString& EGN)
{
	if (!loggedData.loggedThirdParty || loggedData.type != UserType::ThirdParty)
	{
		throw std::invalid_argument("Third-paty employee isn't logged in!");
	}

	size_t idx = findUserByEGN(EGN);

	if (idx == _users.size())
	{
		throw std::invalid_argument("User with such EGN doesn't exist!");
	}

	Client* client = dynamic_cast<Client*>(_users[idx].get());

	if (!client)
	{
		throw std::invalid_argument("User with such EGN isn't client!");
	}

	client->addCheque(std::move(Cheque(code,sum)));
	client->addMessage(std::move("You have a check assigned to you by " + loggedData.logged->getFirstName()+" Code: " + code));

}

void BankingSystem::writeToFile() const
{
	saveUsers();
	saveBanks();
}

void BankingSystem::readFromFile()
{
	loadUsers();
	loadBanks();
}