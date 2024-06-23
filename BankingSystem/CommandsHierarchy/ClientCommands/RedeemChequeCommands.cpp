#include "RedeemChequeCommands.h"

RedeemChequeCommands::RedeemChequeCommands(Client& ref) : _ref(ref)
{
}

Commands* RedeemChequeCommands::clone() const
{
	return new RedeemChequeCommands(*this);
}

void RedeemChequeCommands::execute(BankingSystem* system)
{
	MyString bankName, code;
	int accountId;

	std::cout << "Enter bank name>> ";
	std::cin >> bankName;
	std::cout << "Enter banking account ID>> ";
	std::cin >> accountId;
	std::cout << "Enter cheque verification unique code>> ";
	std::cin >> code;

	try
	{
		Bank& bankRef = system->getBankByName(bankName);
		Cheque& chequeRef = _ref.getCheque(code);
		bankRef.changeBalanceOfAccount(accountId, chequeRef.withdrawCash());
		_ref.removeCheque(code);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}
