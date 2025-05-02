#pragma once
#include "../Command.h"

class ValidateTaskCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system) override;
};

