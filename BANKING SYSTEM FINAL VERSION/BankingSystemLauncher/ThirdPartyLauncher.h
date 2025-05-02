#pragma once
#include "../Components/BankingSystem.h"
#include "../CommandsHierarchy/ThirdPartyCommands/SendChequeCommands.h"

class ThirdPartyLauncher
{
	static void printCommands();

public:

	static void manageThirdParty(ThirdPartyEmployee* emp, BankingSystem* system);
};

