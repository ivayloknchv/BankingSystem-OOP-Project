#pragma once
#include "AccountPlaceholderTask.h"
#include "Account.h"

class CloseAccountTask : public AccountPlaceholderTask
{


public:

	CloseAccountTask(const Account* accptr);

	Task* clone() const override;

	void getTaskPreview() const override;

	void viewTask() const override;
};

