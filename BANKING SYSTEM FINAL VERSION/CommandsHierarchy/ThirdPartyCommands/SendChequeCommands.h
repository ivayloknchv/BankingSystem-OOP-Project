#pragma once
#include "ThirdPartyCommands.h"

class SendChequeCommands : public ThirdPartyCommands
{

public:

	SendChequeCommands(ThirdPartyEmployee& ref);

	Commands* clone() const override;
	void execute(BankingSystem* system) override;
};

