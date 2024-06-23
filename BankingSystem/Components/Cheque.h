#pragma once
#include "MyString.h"

class Cheque
{
	MyString _uniqueCode = "Unknown";
	double _sum = 0.0;
	bool _redeemed = false;
public:

	Cheque() = default;
	Cheque(const MyString& uniqueCode, double sum);
	Cheque(MyString&& uniqueCode, double sum);

	bool isValidCode(const MyString& code) const;

	bool isRedeemed() const;

	double withdrawCash();
};

