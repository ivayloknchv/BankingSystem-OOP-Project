#include "SendChequeCommands.h"

static bool isValidCode(const MyString& code)
{
	if (code.getSize() != 3)
	{
		return false;
	}

	const char* str = code.c_str();

	while (*str != '\0')
	{
		if (!((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z') || (*str >= '0' && *str <= '9')))
		{
			return false;
		}
		str++;
	}

	return true;
}

SendChequeCommands::SendChequeCommands(const ThirdPartyEmployee& ref) : _ref(ref)
{}

Commands* SendChequeCommands::clone() const
{
	return new SendChequeCommands(*this);
}

void SendChequeCommands::execute(BankingSystem* system)
{
	MyString EGN, code;
	double sum = 0.00;

	std::cout << "Enter cheque sum>> ";
	std::cin >> sum;
	std::cout << "Enter unique code>> ";
	std::cin >> code;
	std::cout << "Enter EGN of recipient>> ";
	std::cin >> EGN;

	try
	{
		if (!isValidCode(code))
		{
			throw std::invalid_argument("Invalid unique code. Code must be 3 symbols, only letters and digits allowed!");
		}

		Client& clientRef = system->getClientByEGN(EGN);
		clientRef.addCheque(Cheque(code, sum));
		clientRef.addMessage("You have a check assigned to you by " + _ref.getFirstName());
	}

	catch(std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}
