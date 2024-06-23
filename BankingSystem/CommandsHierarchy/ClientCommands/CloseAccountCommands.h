#pragma once
#include "ClientCommands.h"

class CloseAccountCommands : public ClientCommands
{
	const Client& _ref;

public:

	CloseAccountCommands(const Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

