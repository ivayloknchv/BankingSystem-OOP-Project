#pragma once
#include "BankerCommands.h"

class ValidateTaskCommands : public BankerCommands
{
public:

	ValidateTaskCommands(Banker& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

