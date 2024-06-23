#pragma once
#include "ClientCommands.h"
#include "../../UsersHierarchy/Client.h"

class ShowMessagesCommands : public ClientCommands
{

public:

	ShowMessagesCommands(Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

