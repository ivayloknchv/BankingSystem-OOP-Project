#pragma once
#include "../Command.h"

class ApproveTaskCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system);
};

