#include "Task.h"
#include <utility>
#include "../Components/BankingSystem.h"

Task::Task(TaskType type) : _type(type)
{
}

Task::Task(TaskType type, const MyString& firstName, const MyString& lastName, const MyString& EGN, unsigned age) : _type(type),
_firstName(firstName), _lastName(lastName), _EGN(EGN), _age(age)
{
}

Task::Task(TaskType type, MyString&& firstName, MyString&& lastName, MyString&& EGN, unsigned age) : _type(type),
_firstName(std::move(firstName)), _lastName(std::move(lastName)), _EGN(std::move(EGN)), _age(age)
{

}

TaskType Task::getType() const
{
	return _type;
}

void Task::viewTask() const
{
	std::cout << "Name: " << _firstName << " " << _lastName << std::endl;
	std::cout << "EGN: " << _EGN << std::endl;
	std::cout << "Age: " << _age << std::endl;
}

void Task::disapprove() const
{
	//std::cout << "Enter reason to disapprove>> ";
	//char msg[1024]{};
	//std::cin.getline(msg, 1024);

	//BankingSystem& system = BankingSystem::getInstance();
	//system.getClientByEGN(_EGN).addMessage(std::move(Message(msg)));
}

void Task::writeToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&_type, sizeof(TaskType));
	writeStringToFile(ofs, _firstName);
	writeStringToFile(ofs, _lastName);
	writeStringToFile(ofs, _EGN);
	ofs.write((const char*)&_age, sizeof(unsigned));
}

void Task::readFromFile(std::ifstream& ifs)
{
	_firstName = readStringFromFile(ifs);
	_lastName = readStringFromFile(ifs);
	_EGN = readStringFromFile(ifs);
	ifs.read((char*)&_age, sizeof(unsigned));
}

