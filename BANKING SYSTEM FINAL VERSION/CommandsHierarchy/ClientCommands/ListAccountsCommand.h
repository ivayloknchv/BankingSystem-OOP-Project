#pragma once
#include "../Command.h"

class ListAccountsCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system) override;
};

