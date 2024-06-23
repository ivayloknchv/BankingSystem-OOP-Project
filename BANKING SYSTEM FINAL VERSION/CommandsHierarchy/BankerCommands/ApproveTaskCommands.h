#pragma once
#include "BankerCommands.h"

class ApproveTaskCommands : public BankerCommands
{
	void executeOpenTask(BankingSystem* system, Task* task, size_t taskIdx);

	void executeCloseTask(BankingSystem* system, Task* task, size_t taskIdx);

	void executeChangeTask(BankingSystem* system, Task* task, size_t taskIdx);

public:

	ApproveTaskCommands(Banker& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system);
};

