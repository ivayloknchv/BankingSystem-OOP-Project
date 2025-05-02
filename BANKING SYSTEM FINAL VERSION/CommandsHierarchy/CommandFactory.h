#pragma once
#include "Command.h"
#include "../Helpers/polymorphic_ptr.hpp"
#include "../Helpers/MyString.h"

class CommandFactory
{
public:
	static polymorphic_ptr<Command> createCommand(const MyString& command);
};

