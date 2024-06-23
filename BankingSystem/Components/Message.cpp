#include "Message.h"
#include <utility>
#include <iostream>

Message::Message(const MyString& text) : _text(text)
{
}

Message::Message(MyString&& text) : _text(std::move(text))
{
}

void Message::printMessage() const
{
	std::cout << _text << std::endl;
}
