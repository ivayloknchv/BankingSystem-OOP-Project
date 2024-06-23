#pragma once
#include "ClientCommands.h"
class CheckAvlCommands : public ClientCommands
{
public:

	Commands* clone() const override;
	
	void execute(BankingSystem* system) override;
};

