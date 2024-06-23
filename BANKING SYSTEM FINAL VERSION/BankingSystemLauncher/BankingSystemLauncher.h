#pragma once
#include "../Components/BankingSystem.h"
class BankingSystemLauncher
{
	static void printCommands();
	static void handleLoggedUser(BankingSystem& system);

public:

	static void run();
};

