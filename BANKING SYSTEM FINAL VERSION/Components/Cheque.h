#pragma once
#include <fstream>
#include "../Helpers/MyString.h"
class Cheque
{
	MyString _uniqueCode = "Unknown";
	double _sum = 0.0;

public:

	Cheque() = default;
	Cheque(const MyString& uniqueCode, double sum);
	Cheque(MyString&& uniqueCode, double sum);

	bool isValidCode(const MyString& code) const;

	double getSum() const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};

