#pragma once
#include "MyString.h"
#include "../TasksHierarchy/Task.h"
#include <fstream>

void writeStringToFile(std::ofstream& ofs, const MyString& str);
MyString readStringFromFile(std::ifstream& ifs);
bool stringHasDigitsOnly(const char* str);
bool isCapitalLetter(char ch);
bool isValidAge(unsigned age);
bool hasSmallLetersOnly(const char* str);