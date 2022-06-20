#include "pch.h"
#include "PrimeGenerator/GeneratePrimeNumbersSet.h"

TEST_CASE("GeneratePrimeNumbersSet() tests on create sets functions and CrossSet()")
{
	std::set<int> set1 = { 2, 3, 5, 7 , 11, 13, 17, 19, 23 };
	CHECK(GeneratePrimeNumbersSet(23) == set1);
	CHECK(GeneratePrimeNumbersSet(1008).size() == 168);
	
	CHECK(GeneratePrimeNumbersSet(10000).size() == 1229);
	//CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);

	std::set<int> result = { 2, 4, 6, 8, 20 };
	//CHECK(CrossSet(set1, set2) == result);
}