#include "BankingSystem.h"
#include <stdexcept>
#include <utility>

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

void BankingSystem::logIn(const MyString& EGN, const MyString& password)
{
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

void BankingSystem::logOut()
{
	loggedData.logged = nullptr;
	loggedData.type = LoggedType::Unknown;
}

LoggedType BankingSystem::getLoggedType() const
{
	return loggedData.type;
}

User* BankingSystem::getLoggedUser()
{
	return loggedData.logged;
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
