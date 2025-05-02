#pragma once
#include "../Components/BankingSystem.h"
#include <iostream>
#include <stdexcept>

class Command
{
public:

	virtual void execute(BankingSystem* system) = 0;
	virtual Command* clone() const = 0;
	virtual ~Command() = default;
};

