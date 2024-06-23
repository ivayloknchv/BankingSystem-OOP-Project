#pragma once
#include "../Commands.h"
class ClientCommands : public Commands
{
protected:

	Client& _ref;

public:

	ClientCommands(Client& ref);
};

