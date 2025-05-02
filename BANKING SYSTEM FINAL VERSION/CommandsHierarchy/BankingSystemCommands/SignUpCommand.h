#pragma once
#include "../Command.h"

class SignUpCommand : public Command
{
private:

	void registerClient(BankingSystem* system);
	void registerBanker(BankingSystem* system);
	void registerThirdParty(BankingSystem* system);

public:
	Command* clone() const override;
	void execute(BankingSystem* system) override;
};

