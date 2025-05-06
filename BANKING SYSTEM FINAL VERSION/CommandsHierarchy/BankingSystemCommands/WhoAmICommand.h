#pragma once
#include "../Command.h"

class WhoAmICommand : public Command
{
public:
	void execute(BankingSystem* system) const override;
	Command* clone() const override;
};

