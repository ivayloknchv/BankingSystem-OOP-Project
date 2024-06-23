#include "Cheque.h"
#include <utility>

Cheque::Cheque(const MyString& uniqueCode, double sum) : _uniqueCode(uniqueCode), _sum(sum)
{}

Cheque::Cheque(MyString && uniqueCode, double sum) : _uniqueCode(std::move(uniqueCode)), _sum(sum)
{}

bool Cheque::isValidCode(const MyString & code) const
{
	return _uniqueCode == code;
}

bool Cheque::isRedeemed() const
{
	return _redeemed;
}

double Cheque::withdrawCash()
{
	double toReturn = _sum;
	_sum = 0;
	_redeemed = true;
	return toReturn;
}

