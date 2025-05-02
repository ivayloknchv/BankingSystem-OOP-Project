#pragma once
#include "../Command.h"

class ExitCommand : public Command
{
public:
	virtual void execute(BankingSystem* system) override;
	virtual Command* clone() const override;
};

