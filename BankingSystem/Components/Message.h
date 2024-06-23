#pragma once
#include "MyString.h"

class Message
{
	MyString _text = "No Text";

public:

	Message() = default;
	Message(const MyString& text);
	Message(MyString&& text);

	void printMessage() const;
};

