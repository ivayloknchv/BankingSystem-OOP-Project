#pragma once
#include "Task.h"

class TaskFactory
{
	static Task* createOpenTask(std::ifstream& ifs);

	static Task* createCloseTask(std::ifstream& ifs);

	static Task* createChangeTask(std::ifstream& ifs);

public:

	static Task* create(std::ifstream& ifs);
};

