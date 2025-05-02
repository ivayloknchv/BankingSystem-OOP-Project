#pragma once
#include "../Command.h"

class ViewTaskCommand : public Command
{
public:
	Command* clone() const override;
	void execute(BankingSystem* system);
};

