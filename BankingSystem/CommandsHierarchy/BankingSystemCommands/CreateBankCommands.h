#pragma once
#include "BankingSystemCommands.h"

class CreateBankCommands : public BankingSystemCommands
{
public:

	Commands* clone() const override;

	void execute(BankingSystem* system);
};

