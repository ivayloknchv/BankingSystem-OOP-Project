#pragma once
#include "ClientCommands.h"

class CloseAccountCommands : public ClientCommands
{
public:

	CloseAccountCommands(Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

