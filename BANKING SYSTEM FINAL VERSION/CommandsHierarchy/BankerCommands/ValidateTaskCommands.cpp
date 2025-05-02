#include "ValidateTaskCommands.h"
#include "../../TasksHierarchy/ChangeBankTask.h"
ValidateTaskCommands::ValidateTaskCommands(Banker& ref) : BankerCommands(ref)
{
}

Commands* ValidateTaskCommands::clone() const
{
	return new ValidateTaskCommands(*this);
}

void ValidateTaskCommands::execute(BankingSystem* system)
{
		size_t idx;
		std::cout << "Enter task idx>> ";
		std::cin >> idx;
		Task* newRequest = nullptr;
	try
	{
		Task* taskPtr = _ref.getTask(idx);

		if (taskPtr->getType() == TaskType::Change)
		{
			ChangeBankTask* newTaskPtr = static_cast<ChangeBankTask*>(taskPtr);
			Status st = newTaskPtr->getStatus();

			if (st == Status::NeedsValidation)
			{
				unsigned accId = newTaskPtr->getAccountId();

				Bank& currentBank = system->getBankByName(newTaskPtr->getCurrentBank());
				
				if (currentBank.accountExists(accId))
				{
					newTaskPtr->changeStatus(Status::Approved);
				}
				else
				{
					newTaskPtr->changeStatus(Status::Rejected);
				}
			}
			
			else
			{
				std::cout << "Cannot validate already approved and/or rejected requests!" << std::endl << std::endl;
			}
		}
		else
		{			
			std::cout<<"This task type cannot be validated!"<<std::endl<<std::endl;
		}
	}
	catch (std::invalid_argument& e)
	{
		delete newRequest;
		std::cout << e.what() << std::endl << std::endl;
	}
}
