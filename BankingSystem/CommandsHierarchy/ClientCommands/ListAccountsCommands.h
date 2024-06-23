#pragma once
#include "ClientCommands.h"
#include "Client.h"

class ListAccountsCommands : public ClientCommands
{
	const Client& _ref;

public:

	ListAccountsCommands(const Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

