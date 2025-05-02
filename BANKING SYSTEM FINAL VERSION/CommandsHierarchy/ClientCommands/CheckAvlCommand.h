#pragma once
#include "../Command.h"

class CheckAvlCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system) override;
};

