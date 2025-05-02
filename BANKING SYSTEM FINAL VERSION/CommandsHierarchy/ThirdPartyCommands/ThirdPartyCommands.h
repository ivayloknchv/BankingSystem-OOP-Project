#pragma once
#include "../Commands.h"

class ThirdPartyCommands : public Commands
{
protected:
	ThirdPartyEmployee& _ref;

public:

	ThirdPartyCommands(ThirdPartyEmployee& ref);
};

