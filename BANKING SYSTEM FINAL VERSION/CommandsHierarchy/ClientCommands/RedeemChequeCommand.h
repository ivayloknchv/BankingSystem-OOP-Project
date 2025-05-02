#pragma once
#include "../Command.h"

class RedeemChequeCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system);
};

