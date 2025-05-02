#include "SendChequeCommand.h"

Command* SendChequeCommand::clone() const
{
	return new SendChequeCommand(*this);
}

void SendChequeCommand::execute(BankingSystem* system)
{
	MyString EGN, code;
	double sum = 0.00;

	std::cin >> sum >> EGN >> code;

	try
	{
		system->sendCheque(sum, code, EGN);
		std::cout << "Successfully sent a cheque!";
	}

	catch(std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}
