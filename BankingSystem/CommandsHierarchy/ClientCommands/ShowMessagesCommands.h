#pragma once
#include "ClientCommands.h"
#include "Client.h"

class ShowMessagesCommands : public ClientCommands
{
	const Client& _ref;

public:

	ShowMessagesCommands(const Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

