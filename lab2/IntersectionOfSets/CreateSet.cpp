#include "pch.h"
#include "CreateSet.h"

bool IsDividedBySumOfItsDigits(int val)
{
	std::string number = std::to_string(val);
	int sum = 0;
	for (char digit : number)
	{
		sum += digit - '0';
	}

	if (val % sum == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsSumOfDigitsIsEven(int val)
{
	std::string number = std::to_string(val);
	int sum = 0;
	for (char digit : number)
	{
		sum += digit - '0';
	}

	if (sum % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::set<int> CreateSetOfNumbersFrom1To(const int n, Condition isCondition)
{
	std::set<int> setOfNumbers;
	for (int i = 1; i <= n; i++)
	{
		if (isCondition(i))
		{
			setOfNumbers.insert(i);
		}
	}
	return setOfNumbers;
}
