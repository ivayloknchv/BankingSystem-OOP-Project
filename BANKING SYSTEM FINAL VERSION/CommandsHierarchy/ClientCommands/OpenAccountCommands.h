#pragma once
#include "ClientCommands.h"

class OpenAccountCommands : public ClientCommands
{
public:

	OpenAccountCommands(Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

