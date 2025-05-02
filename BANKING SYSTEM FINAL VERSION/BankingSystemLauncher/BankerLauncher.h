#pragma once
#include "../Components/BankingSystem.h"

class BankerLauncher
{
	static void printCommands();

public:

	static void launchBanker(Banker* banker, BankingSystem* system);
};

