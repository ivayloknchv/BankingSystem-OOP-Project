#pragma once
#include "../ClientCommands/ClientCommands.h"

class ChangeBankCommands : public ClientCommands
{
public:

	ChangeBankCommands(Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

