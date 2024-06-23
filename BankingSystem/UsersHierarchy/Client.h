#pragma once
#include "MyVector.hpp"
#include "User.h"
#include "Cheque.h"
#include "Message.h"
#include "Account.h"


class Client : public User
{
	MyVector<Cheque> _cheques;
	MyVector<Message> _messages;

	size_t findCheque(const MyString& code) const;

public:

	Client() = default;
	Client(const MyString& firstName, const MyString& lastName, const MyString& EGN, const MyString& password, unsigned age);
	Client(MyString&& firstName, MyString&& lastName, MyString&& EGN, MyString&& password, unsigned age);

	void addCheque(const Cheque& cheque);
	void addCheque(Cheque&& cheque);

	void addMessage(const Message& message);
	void addMessage(Message&& message);

	const Cheque& getCheque(const MyString& uniqueCode) const;
	Cheque& getCheque(const MyString& uniqueCode);

	void removeCheque(const MyString& uniqueCode);

	void listMessages() const;

	void whoAmI() const override;

	User* clone() const override;

};

