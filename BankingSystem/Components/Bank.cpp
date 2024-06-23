#include "Bank.h"
#include <utility>
#include <stdexcept>

size_t Bank::findLeastEmployed() const
{
	size_t min = 0;
	size_t size = _bankers.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_bankers[min].getTasksCount() > _bankers[i].getTasksCount())
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
		if (_bankers[i].getEGN() == EGN)
		{
			return i;
		}
	}

	return size;
}

size_t Bank::internalSearchOfAccount(const Account& acc) const
{
	size_t size = _accounts.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_accounts[i] == acc)
		{
			return i;
		}
	}
	return size;
}

size_t Bank::internalSearchOfAccountById(unsigned id) const
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

void Bank::addBanker(const Banker& banker)
{
	_bankers.push_back(banker);
}

void Bank::addbanker(Banker&& banker)
{
	_bankers.push_back(std::move(banker));
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

void Bank::removeAccount(const Account& acc)
{
	size_t idx = internalSearchOfAccount(acc);

	if (idx == _accounts.size())
	{
		throw std::invalid_argument("Such account doesn't exist!");
	}

	_accounts.erase(idx);

}

void Bank::assignTask(Task* ptr)
{
	if (getBankersCount() == 0)
	{
		throw std::invalid_argument("No bankers employes in the bank yet!");
	}
	size_t idx = findLeastEmployed();

	_bankers[idx].addTask(ptr);
}

void Bank::previewAccountsOfClient(const Client& client) const
{
	size_t size = _accounts.size();
	bool isEmpty = true;

	for (size_t i = 0; i < size; i++)
	{
		if (client.getEGN() == _accounts[i].getEGN())
		{
			isEmpty = false;

			_accounts[i].printAccount();
		}
	}

	if (isEmpty)
	{
		std::cout << client.getFirstName() << ' ' << client.getLastName() << ' ' << "is not a client of " << _bankName << std::endl;
	}
}

const Banker& Bank::getBankerByEGN(const MyString& EGN) const
{
	size_t idx = findBankerByEGN(EGN);

	if (idx == _bankers.capacity())
	{
		throw std::invalid_argument("Such banker doesn't exist!");
	}

	return _bankers[idx];
}

const Banker& Bank::getBankerByIdx(size_t idx) const
{
	if (idx < 0 || idx >= _bankers.size())
	{
		throw std::out_of_range("Index out of range");
	}

	return _bankers[idx];
}

Banker& Bank::getBankerByIdx(size_t idx)
{
	if (idx < 0 || idx >= _bankers.size())
	{
		throw std::out_of_range("Index out of range");
	}

	return _bankers[idx];
}

const Account& Bank::getAccountById(size_t id) const
{
	size_t idx = internalSearchOfAccountById(id);

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

void Bank::checkAccountBalance(unsigned id) const
{
	size_t idx = internalSearchOfAccountById(id);

	if (idx == _accounts.size())
	{
		throw std::invalid_argument("Account with this ID doesn't exist");
	}

	std::cout << "Balance: "<<_accounts[idx].getBalance() << '$' << std::endl;
}

void Bank::changeBalanceOfAccount(unsigned id, double sum)
{
	size_t idx = internalSearchOfAccountById(id);

	if (idx == _accounts.size())
	{
		throw std::invalid_argument("Account with this ID doesn't exist");
	}
	_accounts[idx].addBalance(sum);
}
