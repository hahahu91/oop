#include "pch.h"

bool ReadFileWithDoubleNumbers(const std::string& fileName, std::vector<double>& v)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Failed to open file for reading\n";
		return false;
	}
	double number = 0;

	while (file >> number)
	{
		v.push_back(number);
	}

	if (!file.eof())
	{
		std::cout << "Reading error\n";
		return false;
	}
	return true;
}
