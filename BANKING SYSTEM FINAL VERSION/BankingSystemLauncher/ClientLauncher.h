#pragma once
#include "../Components/BankingSystem.h"

class ClientLauncher
{
	static void printCommands();
public:

	static void manageClient(Client* client, BankingSystem* bs);
};

