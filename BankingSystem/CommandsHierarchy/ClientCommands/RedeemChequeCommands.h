#pragma once
#include "ClientCommands.h"

class RedeemChequeCommands : public ClientCommands
{
	Client& _ref;

public:

	RedeemChequeCommands(Client& ref);

	Commands* clone() const override;

	void execute(BankingSystem* system);

};

