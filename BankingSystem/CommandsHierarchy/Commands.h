#pragma once
#include "BankingSystem.h"
#include <iostream>
#include <stdexcept>

class Commands
{
public:

	virtual void execute(BankingSystem* system) = 0;
	virtual Commands* clone() const = 0;
	virtual ~Commands() = default;
};

