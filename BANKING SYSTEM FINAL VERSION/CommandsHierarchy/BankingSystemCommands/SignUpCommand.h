#pragma once
#include "../Command.h"

class SignUpCommand : public Command
{
private:

	void registerClient(BankingSystem* system) const;
	void registerBanker(BankingSystem* system) const;
	void registerThirdParty(BankingSystem* system) const;

public:
	Command* clone() const override;
	void execute(BankingSystem* system) const override;
};

