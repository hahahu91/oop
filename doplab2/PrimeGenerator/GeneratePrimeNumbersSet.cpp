#include "pch.h"
#include "GeneratePrimeNumbersSet.h"
#include <vector>
#define MAX_NUMBERS 100000000

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound <= MAX_NUMBERS)
	{
		std::vector<bool> isPrime(upperBound + 1, true);
		isPrime[0] = false;
		isPrime[1] = false;

		int j;
		std::set<int> primeNumbers;

		for (int i = 2; i < upperBound + 1; i++)
		{
			if (isPrime[i] == true)
			{
				primeNumbers.insert(i);
				j = 0;
				while (j * i + i * i < upperBound + 1)
				{

					isPrime[i * i + j * i] = false;
					j++;
				}
			}
		}
		return primeNumbers;
	}
	else
	{
		return {};
	}
}