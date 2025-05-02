#pragma once
#include "ClientCommands.h"
#include "../../UsersHierarchy/Client.h"

class ListAccountsCommands : public ClientCommands
{
public:

	ListAccountsCommands(Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

