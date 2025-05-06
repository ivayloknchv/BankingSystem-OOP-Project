#pragma once
#include "../Command.h"

class ViewTaskCommand : public Command
{
public:
	void execute(BankingSystem* system) const override;
	Command* clone() const override;
};

