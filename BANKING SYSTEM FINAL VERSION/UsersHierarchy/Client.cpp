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

	_cheques.erase(idx);
}

void Client::listMessages() const
{
	size_t size = _messages.size();

	if (size == 0)
	{
		std::cout << "No messages received!" << std::endl;
	}

	std::cout << "MAILBOX:" << std::endl;
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

void Client::writeToFile(std::ofstream& ofs) const
{
	UserType tp = UserType::Client;
	ofs.write((const char*)&tp, sizeof(tp));

	User::writeToFile(ofs);

	size_t chequesCount = _cheques.size();
	ofs.write((const char*)(&chequesCount), sizeof(size_t));

	for (size_t i = 0; i < chequesCount; i++)
	{
		_cheques[i].writeToFile(ofs);
	}

	size_t messagesCount = _messages.size();

	ofs.write((const char*)&messagesCount, sizeof(size_t));

	for (size_t i = 0; i < messagesCount; i++)
	{
		_messages[i].writeToFile(ofs);
	}
}

void Client::readFromFile(std::ifstream& ifs)
{
	User::readFromFile(ifs);

	size_t chequesCount = 0;
	ifs.read((char*)&chequesCount, sizeof(size_t));

	for (size_t i = 0; i < chequesCount; i++)
	{
		Cheque temp;
		temp.readFromFile(ifs);
		_cheques.push_back(temp);
	}

	size_t messagesCount = 0;
	ifs.read((char*)&messagesCount, sizeof(size_t));

	for (size_t i = 0; i < messagesCount; i++)
	{
		Message temp;
		temp.readFromFile(ifs);
		_messages.push_back(temp);
	}
}

void Client::help() const
{
	std::cout << "check_avl [bank_name] [account_number]" << std::endl;
	std::cout << "open [bank_name]" << std::endl;
	std::cout << "close [bank_name] [account_number]" << std::endl;
	std::cout << "redeem [bank_name] [account_number] [verification_code]" << std::endl;
	std::cout << "change [new_bank_name] [current_bank_name] [account_number]" << std::endl;
	std::cout << "list [bank_name]" << std::endl;
	std::cout << "messages" << std::endl;
}


