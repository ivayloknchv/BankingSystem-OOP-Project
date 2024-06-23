#include "HelperFuncs.h"

void writeStringToFile(std::ofstream& ofs, const MyString& str)
{
	int len = str.getSize();
	ofs.write((const char*)&len, sizeof(len));
	ofs.write((const char*)str.c_str(), str.getSize()*sizeof(char));
}

MyString readStringFromFile(std::ifstream& ifs)
{
	int len = 0;

	ifs.read((char*)&len, sizeof(len));

	char* buff = new char[len + 1]{};

	ifs.read((char*)buff, sizeof(char) * len);

	buff[len] = '\0';

	MyString toReturn = buff;

	delete[] buff;

	return toReturn;
}

bool stringHasDigitsOnly(const char* str)
{
	size_t len = strlen(str);

	for (size_t i = 0; i < len; i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return false;
		}
	}

	return true;
}

bool isCapitalLetter(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

bool isValidAge(unsigned age)
{
	return age>=18;
}

bool hasSmallLetersOnly(const char* str)
{
	if (!str)
	{
		return false;
	}
	
	size_t len = strlen(str);

	for (size_t i = 0; i < len; i++)
	{
		if (!(str[i] >= 'a' && str[i] <= 'z'))
		{
			return false;
		}
	}
	return true;
}

