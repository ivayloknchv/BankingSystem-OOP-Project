#pragma once
#include "../Commands.h"

class BankerCommands : public Commands
{
protected:

	Banker& _ref;

public:

	BankerCommands(Banker& ref);
};

