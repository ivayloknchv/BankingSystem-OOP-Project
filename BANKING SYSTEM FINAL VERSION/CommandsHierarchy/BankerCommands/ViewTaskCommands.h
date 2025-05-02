#pragma once
#include "BankerCommands.h"

class ViewTaskCommands : public BankerCommands
{
public:

	ViewTaskCommands(Banker& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system);
};

