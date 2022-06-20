#include "pch.h"
#include "IntersectionOfSets/CreateSet.h"
#include "IntersectionOfSets/CrossSet.h"

TEST_CASE("CreateSetOfNumbersFrom1To() tests on create sets functions and CrossSet()")
{
	std::set<int> set1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 18 , 20};
	CHECK(CreateSetOfNumbersFrom1To(20, &IsDividedBySumOfItsDigits) == set1);

	std::set<int> set2 = { 2, 4, 6, 8, 11, 13, 15, 17, 19, 20};
	CHECK(CreateSetOfNumbersFrom1To(20, &IsSumOfDigitsIsEven) == set2);

	std::set<int> result = { 2, 4, 6, 8, 20 };
	CHECK(CrossSet(set1, set2) == result);
	
}