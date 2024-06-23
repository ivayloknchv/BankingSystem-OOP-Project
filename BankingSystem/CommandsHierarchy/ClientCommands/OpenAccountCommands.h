#pragma once
#include "ClientCommands.h"

class OpenAccountCommands : public ClientCommands
{
	const Client& _ref;

public:

	OpenAccountCommands(const Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

