#include "pch.h"
#include "CountingFrequency\CountingFrequency.cpp"

TEST_CASE("CountingFrequency() Counting frequency of words")
{
	std::map<std::string, int> currentMap;
	std::string str = "one one one two";
	//CountingFrequency(str, currentMap);
	std::string result = "one: 3\ntwo: 1";
	//CHECK(CountingFrequency(str) == result);
}