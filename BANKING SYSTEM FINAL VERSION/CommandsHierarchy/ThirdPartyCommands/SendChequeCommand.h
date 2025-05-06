#pragma once
#include "../Command.h"

class SendChequeCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system) const override;
};

