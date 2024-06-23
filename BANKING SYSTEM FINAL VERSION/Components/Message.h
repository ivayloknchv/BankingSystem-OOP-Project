#pragma once
#include "../Helpers/MyString.h"
#include "../Helpers/HelperFuncs.h"

class Message
{
	MyString _text = "No Text";

public:

	Message() = default;
	Message(const MyString& text);
	Message(MyString&& text);

	void printMessage() const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};

