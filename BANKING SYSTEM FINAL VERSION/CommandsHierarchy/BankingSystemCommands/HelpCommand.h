#pragma once
#include "../Command.h"

class HelpCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system) const override;
};

