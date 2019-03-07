#include "pch.h"
#include "ProcessVector/MultByMinElement.h"
#include "ProcessVector/ReadFileWithDoubleNumbers.h"

TEST_CASE("MultByMinElement() return vector multiplied by min element ")
{
	std::vector<double> v = { 3.1451, 3.7864, 2, 5.123, 9871.12341, 32.412 };
	std::vector<double> result = { 6.2902, 7.5728, 4, 10.246, 19742.24682, 64.824 }; 
	MultByMinElement(v);
	CHECK(v == result);

	std::vector<double> v2 = { 0, - 1, 731264.213, 78731.121344, 10412 };
	std::vector<double> result2 = { 0, 1, -731264.213, - 78731.121344, - 10412 };
	MultByMinElement(v2);
	CHECK(v2 == result2);
}
