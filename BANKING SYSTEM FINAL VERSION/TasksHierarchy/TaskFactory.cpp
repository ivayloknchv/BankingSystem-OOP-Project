#include "TaskFactory.h"
#include "OpenAccountTask.h"
#include "CloseAccountTask.h"
#include "ChangeBankTask.h"

Task* TaskFactory::createOpenTask(std::ifstream& ifs)
{
	OpenAccountTask* ptr = new OpenAccountTask();
	ptr->readFromFile(ifs);
	return ptr;
}

Task* TaskFactory::createCloseTask(std::ifstream& ifs)
{
	CloseAccountTask* ptr = new CloseAccountTask();
	ptr->readFromFile(ifs);
	return ptr;
}

Task* TaskFactory::createChangeTask(std::ifstream& ifs)
{
	ChangeBankTask* ptr = new ChangeBankTask();
	ptr->readFromFile(ifs);

	return ptr;
}

Task* TaskFactory::create(std::ifstream& ifs)
{
	TaskType type;

	ifs.read((char*)&type, sizeof(TaskType));

	switch (type)
	{
		case (TaskType::Open):
			return createOpenTask(ifs);

		case (TaskType::Close):
			return createCloseTask(ifs);

		case (TaskType::Change):
			return createChangeTask(ifs);
	}

	return nullptr;
}
