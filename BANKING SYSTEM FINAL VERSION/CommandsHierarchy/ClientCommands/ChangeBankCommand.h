#pragma once
#include "../Command.h"

class ChangeBankCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system) override;
};

