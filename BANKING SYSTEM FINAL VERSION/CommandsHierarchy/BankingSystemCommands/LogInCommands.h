#pragma once
#include "BankingSystemCommands.h"

class LogInCommands : public BankingSystemCommands
{
public:

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

