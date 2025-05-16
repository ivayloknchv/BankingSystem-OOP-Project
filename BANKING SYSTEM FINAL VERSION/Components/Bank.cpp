#include "Bank.h"
#include <utility>
#include <stdexcept>

size_t Bank::findLeastEmployed() const
{
	size_t min = 0;
	size_t size = _bankers.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_bankers[min]->getTasksCount() > _bankers[i]->getTasksCount())
		{
			min = i;
		}
	}
	return min;
}

size_t Bank::findBankerByEGN(const MyString& EGN) const
{
	size_t size=_bankers.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_bankers[i]->getEGN() == EGN)
		{
			return i;
		}
	}

	return size;
}

size_t Bank::findAccountById(unsigned id) const
{
	size_t size = _accounts.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_accounts[i].getId() == id)
		{
			return i;
		}
	}
	return size;
}

Bank::Bank(const MyString& bankName) : _bankName(bankName)
{
}

Bank::Bank(MyString&& bankName) : _bankName(std::move(bankName))
{
}

void Bank::addBanker(Banker* banker)
{
	_bankers.push_back(banker);
}

void Bank::addAccount(const Account& acc)
{
	_accounts.push_back(acc);
}

void Bank::addAccount(Account&& acc)
{
	_accounts.push_back(std::move(acc));
}

const MyString& Bank::getBankName() const
{
	return _bankName;
}

size_t Bank::getBankersCount() const
{
	return _bankers.size();
}

void Bank::removeAccountByID(size_t id)
{
	size_t idx = findAccountById(id);

	if (idx == _accounts.size())
	{
		throw std::invalid_argument("Such account doesn't exist!");
	}

	_accounts.erase(idx);
}

bool Bank::accountExists(unsigned accId) const
{
	size_t idx = findAccountById(accId);

	if (idx == _accounts.size())
	{
		return false;
	}

	return true;
}

void Bank::assignTask(Task* ptr)
{
	if (getBankersCount() == 0)
	{
		throw std::invalid_argument("No bankers employes in the bank yet!");
	}
	size_t idx = findLeastEmployed();

	_bankers[idx]->addTask(ptr);
}

void Bank::assignTask(const polymorphic_ptr<Task>& task)
{
	if (getBankersCount() == 0)
	{
		throw std::invalid_argument("No bankers employes in the bank yet!");
	}
	size_t idx = findLeastEmployed();

	_bankers[idx]->addTask(task);
}

void Bank::previewAccountsOfClient(const MyString& clientEGN) const
{
	size_t size = _accounts.size();
	bool isEmpty = true;

	for (size_t i = 0; i < size; i++)
	{
		if (clientEGN == _accounts[i].getEGN())
		{
			isEmpty = false;

			_accounts[i].printAccount();
		}
	}

	if (isEmpty)
	{
		std::cout << "Client with EGN " << clientEGN << ' ' << "is not a client of " << _bankName << std::endl;
	}
}

const Banker* Bank::getBankerByEGN(const MyString& EGN) const
{
	size_t idx = findBankerByEGN(EGN);

	if (idx == _bankers.capacity())
	{
		throw std::invalid_argument("Such banker doesn't exist!");
	}

	return _bankers[idx];
}

const Banker* Bank::getBankerByIdx(size_t idx) const
{
	if (idx < 0 || idx >= _bankers.size())
	{
		throw std::out_of_range("Index out of range");
	}

	return _bankers[idx];
}

Banker* Bank::getBankerByIdx(size_t idx)
{
	if (idx < 0 || idx >= _bankers.size())
	{
		throw std::out_of_range("Index out of range");
	}

	return _bankers[idx];
}

const Account& Bank::getAccountById(size_t id) const
{
	size_t idx = findAccountById(id);

	if (idx == _accounts.size())
	{
		throw std::invalid_argument("Account with this ID doesn't exist in the bank!");
	}

	return _accounts[idx];
}

bool Bank::bankerExists(const MyString& EGN) const
{
	return (findBankerByEGN(EGN) != _bankers.size());
}

void Bank::changeBalanceOfAccount(unsigned id, const MyString& EGN, double sum)
{
	size_t idx = findAccountById(id);

	if (idx == _accounts.size())
	{
		throw std::invalid_argument("Account with this ID doesn't exist");
	}

	if (_accounts[idx].getEGN() != EGN)
	{
		throw std::invalid_argument("Trying to access someone else's account!");
	}

	_accounts[idx].addBalance(sum);
}

void Bank::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, _bankName);

	size_t bankersCount = _bankers.size();

	ofs.write((const char*)&bankersCount, sizeof(size_t));

	for (size_t i = 0; i < bankersCount; i++)
	{
		writeStringToFile(ofs, _bankers[i]->getEGN());
	}

	size_t accountsCount = _accounts.size();

	ofs.write((const char*)&accountsCount, sizeof(size_t));

	for (size_t i = 0; i < accountsCount; i++)
	{
		_accounts[i].writeToFile(ofs);
	}
}

void Bank::readFromFile(std::ifstream& ifs, MyVector<polymorphic_ptr<User>>& users)
{
	_bankName = readStringFromFile(ifs);

	size_t bankersCount = 0;

	ifs.read((char*)&bankersCount, sizeof(size_t));

	for (size_t i = 0; i < bankersCount; i++)
	{
		MyString EGN = readStringFromFile(ifs);

		for (size_t j = 0; j < users.size(); j++)
		{	
			if (users[j]->getEGN() == EGN)
			{
				Banker* banker = dynamic_cast<Banker*>(users[j].get());
				_bankers.push_back(banker);
			}
		}
	}

	size_t accountsCount = 0;

	ifs.read((char*)&accountsCount, sizeof(size_t));

	for (size_t i = 0; i < accountsCount; i++)
	{
		Account temp;
		temp.readFromFile(ifs);

		_accounts.push_back(std::move(temp));
	}
}
