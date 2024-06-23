#include "Cheque.h"
#include <utility>
#include "../Helpers/HelperFuncs.h"

Cheque::Cheque(const MyString& uniqueCode, double sum) : _uniqueCode(uniqueCode), _sum(sum)
{}

Cheque::Cheque(MyString && uniqueCode, double sum) : _uniqueCode(std::move(uniqueCode)), _sum(sum)
{}

bool Cheque::isValidCode(const MyString & code) const
{
	return _uniqueCode == code;
}


double Cheque::getSum() const
{
	return _sum;
}

void Cheque::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, _uniqueCode);
	ofs.write((const char*)&_sum, sizeof(double));
}

void Cheque::readFromFile(std::ifstream& ifs)
{
	_uniqueCode = readStringFromFile(ifs);
	ifs.read((char*)&_sum, sizeof(double));
}

