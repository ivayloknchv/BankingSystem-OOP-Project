#pragma once
#include "ClientCommands.h"
class CheckAvlCommands : public ClientCommands
{
public:

	CheckAvlCommands(Client& ref);

	Commands* clone() const override;
	
	void execute(BankingSystem* system) override;
};

