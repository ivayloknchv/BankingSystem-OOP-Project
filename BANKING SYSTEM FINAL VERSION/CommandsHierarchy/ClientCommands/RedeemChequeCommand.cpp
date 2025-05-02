#include "RedeemChequeCommand.h"

Command* RedeemChequeCommand::clone() const
{
	return new RedeemChequeCommand(*this);
}

void RedeemChequeCommand::execute(BankingSystem* system)
{
	MyString bankName, code;
	unsigned accountId;

	std::cout << "Enter bank name>> ";
	std::cin >> bankName >> code >> accountId;

	try
	{
		system->redeemCheque(bankName, accountId, code);
		std::cout << "Cheque redeeemed! Check your account balance!";
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
