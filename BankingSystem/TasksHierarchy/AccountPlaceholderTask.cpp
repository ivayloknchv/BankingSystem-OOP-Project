#include "AccountPlaceholderTask.h"

AccountPlaceholderTask::AccountPlaceholderTask(TaskType type, const Account* ptr) : Task(type), _accPtr(ptr)
{}
