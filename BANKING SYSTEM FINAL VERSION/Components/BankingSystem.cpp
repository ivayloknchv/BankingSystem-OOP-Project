#include "BankingSystem.h"
#include <stdexcept>
#include <utility>
#include "../TasksHierarchy/OpenAccountTask.h"
#include "../TasksHierarchy/CloseAccountTask.h"
#include "../TasksHierarchy/ChangeBankTask.h"

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
	size_t clientIdx = findClientByEGN(user->getEGN());

	if (clientIdx != _clients.size())
	{
		return true;
	}

	size_t thirdPartyIdx = findThirdPartyByEGN(user->getEGN());

	if (thirdPartyIdx != _thirdParty.size())
	{
		return true;
	}

	size_t banksSize = _banks.size();
	
	for (size_t i = 0; i < banksSize; i++)
	{
		if (_banks[i].bankerExists(user->getEGN()))
		{
			return true;
		}
	}

	return false;
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

size_t BankingSystem::findClientByEGN(const MyString& EGN) const
{
	size_t size = _clients.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_clients[i].getEGN() == EGN)
		{
			return i;
		}
	}

	return size;
}

size_t BankingSystem::findThirdPartyByEGN(const MyString& EGN) const
{
	size_t size = _thirdParty.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_thirdParty[i].getEGN() == EGN)
		{
			return i;
		}
	}

	return size;
}

void BankingSystem::saveClients() const
{
	std::ofstream ofs("clients.dat", std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}

	size_t clientsCount = _clients.size();
	ofs.write((const char*)&clientsCount, sizeof(size_t));

	for (size_t i = 0; i < clientsCount; i++)
	{
		_clients[i].writeToFile(ofs);
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

void BankingSystem::saveThirdParty() const
{
	std::ofstream ofs("thirdParty.dat", std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}

	size_t thirdPartyCount = _thirdParty.size();
	ofs.write((const char*)&thirdPartyCount, sizeof(size_t));

	for (size_t i = 0; i < thirdPartyCount; i++)
	{
		_thirdParty[i].writeToFile(ofs);
	}

	ofs.close();
}

void BankingSystem::loadClients()
{
	std::ifstream ifs("clients.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t clientsCount = 0;

	ifs.read((char*)&clientsCount, sizeof(size_t));

	for (size_t i = 0; i < clientsCount; i++)
	{
		Client temp;
		temp.readFromFile(ifs);
		_clients.push_back(std::move(temp));
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
		temp.readFromFile(ifs);
		_banks.push_back(std::move(temp));
	}

	ifs.close();
}

void BankingSystem::loadThirdParty()
{
	std::ifstream ifs("thirdParty.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t thirdPartyCount = 0;

	ifs.read((char*)&thirdPartyCount, sizeof(size_t));

	for (size_t i = 0; i < thirdPartyCount; i++)
	{
		ThirdPartyEmployee temp;
		temp.readFromFile(ifs);
		_thirdParty.push_back(std::move(temp));
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

void BankingSystem::addClient(const Client& client)
{
	if (userExists(&client))
	{
		throw std::invalid_argument("User with this EGN is already registrated!");
	}

	_clients.push_back(client);
}

void BankingSystem::addClient(Client&& client)
{
	if (userExists(&client))
	{
		throw std::invalid_argument("User with this EGN is already registrated!");
	}

	_clients.push_back(std::move(client));
}

void BankingSystem::addBanker(const Banker& banker, const MyString& bankName)
{
	size_t idx = findBankByName(bankName);

	if (idx == _banks.size())
	{
		throw std::invalid_argument("This bank doesn't exist in the system!");
	}

	if (userExists(&banker))
	{
		throw std::invalid_argument("Invalid banker data! User with this EGN is already registrated!");
	}

	_banks[idx].addBanker(banker);
}

void BankingSystem::addBanker(Banker&& banker, MyString&& bankName)
{
	size_t idx = findBankByName(bankName);

	if (idx == _banks.size())
	{
		throw std::invalid_argument("This bank doesn't exist in the system!");
	}

	if (userExists(&banker))
	{
		throw std::invalid_argument("Invalid banker data! User with this EGN is already registrated!");
	}

	_banks[idx].addBanker(std::move(banker));
}

void BankingSystem::addThirdPartyEmployee(const ThirdPartyEmployee& thirdParty)
{
	if (userExists(&thirdParty))
	{
		throw std::invalid_argument("User with this EGN is already registrated!");
	}

	_thirdParty.push_back(thirdParty);
}

void BankingSystem::addThirdPartyEmployee(ThirdPartyEmployee&& thirdParty)
{
	if (userExists(&thirdParty))
	{
		throw std::invalid_argument("User with this EGN is already registrated!");
	}

	_thirdParty.push_back(std::move(thirdParty));
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
	if (loggedData.logged == nullptr)
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

	//iterate clients
	size_t size = _clients.size();

	for (size_t i = 0; i < size; i++)
	{
		if (isLogInDataValid(EGN, password, &_clients[i]))
		{
			loggedData.logged = &_clients[i];
			loggedData.type = LoggedType::Client;
			return;
		}
	}

	//iterate thirdParty

	size = _thirdParty.size();

	for (size_t i = 0; i < size; i++)
	{
		if (isLogInDataValid(EGN, password, &_thirdParty[i]))
		{
			loggedData.logged = &_thirdParty[i];
			loggedData.type = LoggedType::ThirdParty;
			return;
		}
	}

	//iterate bankers

	size = _banks.size();

	for (size_t i = 0; i < size; i++)
	{
		size_t bankersCount = _banks[i].getBankersCount();

		for (size_t j = 0; j < bankersCount; j++)
		{
			if (isLogInDataValid(EGN, password, &_banks[i].getBankerByIdx(j)))
			{
				loggedData.logged = &_banks[i].getBankerByIdx(j);
				loggedData.type = LoggedType::Banker;
				return;
			}
		}
	}

	throw std::invalid_argument("User with these data details doesn't exist!");
}

void BankingSystem::exit()
{
	loggedData.logged = nullptr;
	loggedData.type = LoggedType::Unknown;
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

const Client& BankingSystem::getClientByEGN(const MyString& EGN) const
{
	size_t idx = findClientByEGN(EGN);

	if (idx == _clients.size())
	{
		throw std::invalid_argument("Client with this EGN doesn't exist!");
	}

	return _clients[idx];
}

Client& BankingSystem::getClientByEGN(const MyString& EGN)
{
	size_t idx = findClientByEGN(EGN);

	if (idx == _clients.size())
	{
		throw std::invalid_argument("Client with this EGN doesn't exist!");
	}

	return _clients[idx];
}

void BankingSystem::checkAvl(const MyString& bankName, unsigned accountID) const
{
	if (!loggedData.logged || loggedData.type!=LoggedType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	const Account& account = getBankByName(bankName).getAccountById(accountID);

	if (account.getEGN() != loggedData.logged->getEGN())
	{
		throw std::invalid_argument("Trying to access someone else's account!");
	}

	account.printAccount();
}

void BankingSystem::openAccount(const MyString& bankName)
{
	if (!loggedData.logged || loggedData.type != LoggedType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	Bank& bank = getBankByName(bankName);

	bank.assignTask(new OpenAccountTask(loggedData.logged->getFirstName(), loggedData.logged->getLastName(),
		loggedData.logged->getEGN(), loggedData.logged->getAge(), bankName));
}

void BankingSystem::closeAccount(const MyString& bankName, unsigned accountID)
{
	if (!loggedData.logged || loggedData.type != LoggedType::Client)
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
	if (!loggedData.logged || loggedData.type != LoggedType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	Bank& bank = getBankByName(bankName);
	Client& client = getClientByEGN(loggedData.logged->getEGN());
	const Cheque& cheque = client.getCheque(code);
	bank.changeBalanceOfAccount(accountID, loggedData.logged->getEGN(), cheque.getSum());
	client.removeCheque(code);

}

void BankingSystem::changeBank(const MyString& newBankName, const MyString& currentBankName, unsigned accountID)
{
	if (!loggedData.logged || loggedData.type != LoggedType::Client)
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
	if (!loggedData.logged || loggedData.type != LoggedType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	getBankByName(bankName).previewAccountsOfClient(loggedData.logged->getEGN());
}

void BankingSystem::viewMessages() const
{
	if (!loggedData.logged || loggedData.type != LoggedType::Client)
	{
		throw std::invalid_argument("Client isn't logged in!");
	}

	getClientByEGN(loggedData.logged->getEGN()).listMessages();
}

void BankingSystem::viewTasks() const
{
	if (!loggedData.logged || loggedData.type != LoggedType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}

	Banker* banker = static_cast<Banker*>(loggedData.logged);

	banker->previewTasks();
}

void BankingSystem::viewTask(unsigned taskIdx) const
{
	if (!loggedData.logged || loggedData.type != LoggedType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}

	Banker* banker = static_cast<Banker*>(loggedData.logged);
	banker->viewTask(taskIdx);
}

void BankingSystem::approveTask(unsigned taskIdx)
{
	if (!loggedData.logged || loggedData.type != LoggedType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}

	Banker* banker = static_cast<Banker*>(loggedData.logged);
	banker->approveTask(taskIdx);
}

void BankingSystem::disapproveTask(unsigned taskIdx)
{
	if (!loggedData.logged || loggedData.type != LoggedType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}

	Banker* banker = static_cast<Banker*>(loggedData.logged);
	banker->disapproveTask(taskIdx);
}

void BankingSystem::validateTask(unsigned taskIdx)
{
	if (!loggedData.logged || loggedData.type != LoggedType::Banker)
	{
		throw std::invalid_argument("Banker isn't logged in!");
	}

	Banker* banker = static_cast<Banker*>(loggedData.logged);
	banker->validateTask(taskIdx);
}

void BankingSystem::sendCheque(double sum, const MyString& code, const MyString& EGN)
{
	if (!loggedData.logged || loggedData.type != LoggedType::ThirdParty)
	{
		throw std::invalid_argument("Third-paty employee isn't logged in!");
	}

	Client& client = getClientByEGN(EGN);
	client.addCheque(std::move(Cheque(code,sum)));
	client.addMessage(std::move("You have a check assigned to you by " + loggedData.logged->getFirstName()+" Code: " + code));

}

void BankingSystem::writeToFile() const
{
	saveClients();
	saveBanks();
	saveThirdParty();
}

void BankingSystem::readFromFile()
{
	loadClients();
	loadBanks();
	loadThirdParty();
}