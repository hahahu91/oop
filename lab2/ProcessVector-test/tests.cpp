#include "pch.h"
#include "ProcessVector/MultByMinElement.h"

TEST_CASE("MultByMinElement() return vector multiplied by min element ")
{
	std::vector<double> v = { 4, 7, 2, 5.5, 9.3, 250 };
	std::vector<double> result = { 8, 14, 4, 11, 18.6, 500 }; 
	MultByMinElement(v);
	CHECK(v == result);

	v = {};
	result = {};
	MultByMinElement(v);
	CHECK(v == result);
}
