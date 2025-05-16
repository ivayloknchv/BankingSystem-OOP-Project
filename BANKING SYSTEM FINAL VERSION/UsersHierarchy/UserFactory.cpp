#include "UserFactory.h"

User* UserFactory::createUser(std::ifstream& ifs)
{
	UserType tp;
	User* ptr = nullptr;
	ifs.read((char*)&tp, sizeof(tp));

	switch (tp) {
	case UserType::Client:
		ptr = new Client();
		ptr->readFromFile(ifs);
		break;
	case UserType::Banker:
		ptr = new Banker();
		ptr->readFromFile(ifs);
		break;
	case UserType::ThirdParty:
		ptr = new ThirdPartyEmployee();
		ptr->readFromFile(ifs);
		break;
	}
	return ptr;
}
