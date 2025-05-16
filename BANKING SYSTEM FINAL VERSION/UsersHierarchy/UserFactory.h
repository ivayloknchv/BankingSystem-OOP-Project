#pragma once
#include "Client.h"
#include "Banker.h"
#include "ThirdPartyEmployee.h"

class UserFactory
{
public:
	static User* createUser(std::ifstream& ifs);
};

