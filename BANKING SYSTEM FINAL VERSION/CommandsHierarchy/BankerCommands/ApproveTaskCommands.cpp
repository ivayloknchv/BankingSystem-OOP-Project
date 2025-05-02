#include "ApproveTaskCommands.h"
#include "../../TasksHierarchy/OpenAccountTask.h"
#include "../../TasksHierarchy/CloseAccountTask.h"
#include "../../TasksHierarchy/ChangeBankTask.h"

static size_t numLen(size_t num)
{
	if (num == 0)
	{
		return 1;
	}

	size_t toReturn = 0;

	while (num != 0)
	{
		toReturn++;
		num /= 10;
	}

	return toReturn;
}

static MyString numToString(size_t num)
{
	size_t len = numLen(num);
	char* data = new char[len + 1]{};

	for (size_t i = 0; i < len; i++)
	{
		data[len - 1 - i] = '0' + (num % 10);
		num /= 10;
	}

	MyString toReturn(data);
	delete[] data;

	return toReturn;
}

void ApproveTaskCommands::executeOpenTask(BankingSystem* system, Task* task, size_t taskIdx)
{
	OpenAccountTask* taskPtr = static_cast<OpenAccountTask*>(task);

	MyString clientEGN = taskPtr->getEGN();
	MyString bank = _ref.getWorkplace();

	Account acc(taskPtr->getFirstName(), taskPtr->getLastName(), clientEGN, taskPtr->getAge(), bank);
	system->getBankByName(bank).addAccount(acc);

	Message msg = "You opened an account in " + bank + "! Your account ID is " + numToString(acc.getId());

	system->getClientByEGN(clientEGN).addMessage(msg);

	_ref.removeTaskAt(taskIdx);

	std::cout << "Successfully opened a new bank account!" << std::endl << std::endl;

}

void ApproveTaskCommands::executeCloseTask(BankingSystem* system, Task* task, size_t taskIdx)
{
	CloseAccountTask* taskPtr = static_cast<CloseAccountTask*>(task);
	
	Bank& bankRef = system->getBankByName(_ref.getWorkplace());

	system->getClientByEGN(taskPtr->getEGN()).addMessage("Your account in " + _ref.getWorkplace() + " was successfully closed!");

	_ref.removeTaskAt(taskIdx);

	bankRef.removeAccountByID(taskPtr->getAccountId());

	std::cout << "Successfully closed bank account!" << std::endl << std::endl;
}

void ApproveTaskCommands::executeChangeTask(BankingSystem* system, Task* task, size_t taskIdx)
{
	ChangeBankTask* taskPtr = static_cast<ChangeBankTask*>(task);

	Status currentSt = taskPtr->getStatus();

	if (currentSt == Status::Approved)
	{
		Bank& bankRef = system->getBankByName(_ref.getWorkplace());
		Bank& oldBank = system->getBankByName(taskPtr->getCurrentBank());

		MyString EGN = taskPtr->getEGN();

		Account newAcc(taskPtr->getFirstName(), taskPtr->getLastName(), EGN, taskPtr->getAge(), bankRef.getBankName());
		newAcc.addBalance(taskPtr->getBalance());

		bankRef.addAccount(newAcc);
		oldBank.removeAccountByID(taskPtr->getAccountId());

		_ref.removeTaskAt(taskIdx);

		Message msg = "You changed your savings account to " + _ref.getWorkplace() + ". Your new ID is " + numToString(newAcc.getId());
		system->getClientByEGN(EGN).addMessage(msg);

		std::cout << "Successfully transferred the bank account!" << std::endl << std::endl;
	}

	else if (currentSt == Status::NeedsValidation)
	{
		std::cout << "Cannot proceed - please make sure "<<taskPtr->getFirstName()<< " is real user by asking the bank!"<<std::endl<<std::endl;
	}

	else if (currentSt == Status::Rejected)
	{
		std::cout << "The request was rejected! No account will be transferred!" << std::endl<<std::endl;
		_ref.removeTaskAt(taskIdx);
		system->getClientByEGN(taskPtr->getEGN()).
			addMessage("Your account transfer from " + taskPtr->getCurrentBank() +" to " + _ref.getWorkplace() +" was rejected!");
	}
}

ApproveTaskCommands::ApproveTaskCommands(Banker& ref) : BankerCommands(ref)
{}

Commands* ApproveTaskCommands::clone() const
{
	return new ApproveTaskCommands(*this);
}

void ApproveTaskCommands::execute(BankingSystem* system)
{
	size_t idx = 0;

	std::cout << "Enter task idx>> ";
	std::cin >> idx;

	try
	{
		Task* currentTask = _ref.getTask(idx);

		if (currentTask->getType() == TaskType::Open)
		{
			executeOpenTask(system, currentTask, idx);
		}
		else if (currentTask->getType() == TaskType::Close)
		{
			executeCloseTask(system, currentTask, idx);
		}
		else if (currentTask->getType() == TaskType::Change)
		{
			executeChangeTask(system, currentTask, idx);
		}
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}
}
