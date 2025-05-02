#pragma once
#include "BankerCommands.h"

class ShowTasksCommands : public BankerCommands
{

public:

	ShowTasksCommands(Banker& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;

};

