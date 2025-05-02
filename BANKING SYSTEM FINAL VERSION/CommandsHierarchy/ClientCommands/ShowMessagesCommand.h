#pragma once
#include "../Command.h"

class ShowMessagesCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system) override;
};

