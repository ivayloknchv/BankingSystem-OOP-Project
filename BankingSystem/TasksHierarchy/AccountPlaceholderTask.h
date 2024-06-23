#pragma once
#include "Task.h"
#include "Account.h"

class AccountPlaceholderTask : public Task
{
protected:

	const Account* _accPtr = nullptr;

public:

	AccountPlaceholderTask(TaskType type, const Account* ptr);
};

