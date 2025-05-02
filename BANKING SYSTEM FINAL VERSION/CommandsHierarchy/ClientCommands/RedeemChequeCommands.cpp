#include "RedeemChequeCommands.h"

RedeemChequeCommands::RedeemChequeCommands(Client& ref) : ClientCommands(ref)
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
		const Cheque& chequeRef = _ref.getCheque(code);
		Account& accRef = bankRef.getAccountById(accountId);

		if (accRef.getEGN() != _ref.getEGN())
		{
			throw std::invalid_argument("Trying to access some else's account!");
		}
		accRef.addBalance(chequeRef.getSum());
		_ref.removeCheque(code);

		std::cout << "Cheque redeeemed! Check your account balance!" << std::endl<<std::endl;
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}
