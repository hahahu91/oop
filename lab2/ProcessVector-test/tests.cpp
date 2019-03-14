#include "pch.h"
#include "ProcessVector/MultByMinElement.h"

TEST_CASE("MultByMinElement() return vector multiplied by min element ")
{
	std::vector<double> v = { 4, 7, 2, 5.5, 9.3, 250 };
	std::vector<double> result = { 8, 14, 4, 11, 18.6, 500 }; 
	MultByMinElement(v);
	CHECK(v == result);

	std::vector<double> v2 = { 0, - 1, 125, 100, 300.25 };
	std::vector<double> result2 = { 0, 1, -125, -100, -300.25 };
	MultByMinElement(v2);
	CHECK(v2 == result2);

	v = {};
	result = {};
	MultByMinElement(v);
	CHECK(v == result);
}
