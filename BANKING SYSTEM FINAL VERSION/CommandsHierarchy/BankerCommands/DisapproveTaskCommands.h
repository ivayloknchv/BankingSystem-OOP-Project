#pragma once
#include "BankerCommands.h"

class DisapproveTaskCommands : public BankerCommands
{
	void sendMessage(BankingSystem* system, Task* task);

public:

	DisapproveTaskCommands(Banker& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

