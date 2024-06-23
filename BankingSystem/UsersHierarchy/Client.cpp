#include "Client.h"
#include <utility>

size_t Client::findCheque(const MyString& code) const
{
	size_t size = _cheques.size();

	for (size_t i = 0; i < size; i++)
	{
		if (_cheques[i].isValidCode(code))
		{
			return i;
		}
	}

	return size;
}

Client::Client(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age)
	:User(firstName, lastName, EGN, password, age)
{
}

Client::Client(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age)
	:User(std::move(firstName), std::move(lastName), std::move(EGN), std::move(password), age)
{
}

void Client::addCheque(const Cheque& cheque)
{
	_cheques.push_back(cheque);
}

void Client::addCheque(Cheque&& cheque)
{
	_cheques.push_back(std::move(cheque));
}

void Client::addMessage(const Message& message)
{
	_messages.push_back(message);
}

void Client::addMessage(Message&& message)
{
	_messages.push_back(std::move(message));
}

const Cheque& Client::getCheque(const MyString& uniqueCode) const
{
	size_t idx = findCheque(uniqueCode);

	if (idx == _cheques.size())
	{
		throw std::invalid_argument("Cheque with this code doesn't exist!");
	}
	return _cheques[idx];
}

Cheque& Client::getCheque(const MyString& uniqueCode)
{
	size_t idx = findCheque(uniqueCode);

	if (idx == _cheques.size())
	{
		throw std::invalid_argument("Cheque with this code doesn't exist!");
	}
	return _cheques[idx];
}

void Client::removeCheque(const MyString& uniqueCode)
{
	size_t idx = findCheque(uniqueCode);

	if (idx == _cheques.size())
	{
		throw std::invalid_argument("Cheque with this code doesn't exist!");
	}

	if (!_cheques[idx].isRedeemed())
	{
		throw std::invalid_argument("Your cheque is full! Why don't you redeem it first before you remove it?");
	}

	_cheques.erase(idx);
}

void Client::listMessages() const
{
	size_t size = _messages.size();

	if (size == 0)
	{
		std::cout << "No messages received!" << std::endl;
	}

	for (size_t i = 0; i < size; i++)
	{
		std::cout << "[" << i + 1 << "] ";
		_messages[i].printMessage();
	}
}

void Client::whoAmI() const
{
	User::whoAmI();
	std::cout << "Status: " << "Client" << std::endl;
}

User* Client::clone() const
{
	return new Client(*this);
}


