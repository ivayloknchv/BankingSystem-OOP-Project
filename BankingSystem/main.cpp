#include <iostream>
#include "Account.h"
#include "Bank.h"
#include "Banker.h"
#include "User.h"
#include "BankingSystem.h"
#include "CreateBankCommands.h"
#include "SignUpCommands.h"

int main()
{
	BankingSystem s;

	CreateBankCommands cr;

	cr.execute(&s);

	SignUpCommands sc;

	sc.execute(&s);

	sc.execute(&s);

	sc.execute(&s);

	return 0;
}