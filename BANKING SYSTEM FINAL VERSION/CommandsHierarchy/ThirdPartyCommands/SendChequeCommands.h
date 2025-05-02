#pragma once
#include "ThirdPartyCommands.h"

class SendChequeCommands : public ThirdPartyCommands
{
	const ThirdPartyEmployee& _ref;

public:

	SendChequeCommands(const ThirdPartyEmployee& ref);

	Commands* clone() const override;
	void execute(BankingSystem* system) override;
};

