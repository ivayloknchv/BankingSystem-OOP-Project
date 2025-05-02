#pragma once
#include "../Command.h"

class HelpCommand : public Command
{
public:
	virtual void execute(BankingSystem* system) override;
	virtual Command* clone() const override;
};

