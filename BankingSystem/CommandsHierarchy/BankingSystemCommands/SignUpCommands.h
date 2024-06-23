#pragma once
#include "BankingSystemCommands.h"

class SignUpCommands : public BankingSystemCommands
{
private:

	void registerClient(BankingSystem* system);
	void registerBanker(BankingSystem* system);
	void registerThirdParty(BankingSystem* system);

public:

	Commands* clone() const override;

	void execute(BankingSystem* system) override;
};

