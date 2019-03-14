#include "pch.h"
#include "CountingFrequency\CalculateWordOccurrence.h"
#include "CountingFrequency\UpdateWordFrequency.h"

TEST_CASE("CalculateWordOccurrence() Counting frequency of words")
{
	std::istringstream input("cat CaT  dog banana BANANA");
	std::map<std::string, int> result = CalculateWordOccurrence(input);
	std::map<std::string, int> expected = { { "cat", 2 }, { "banana", 2 }, { "dog", 1 } };
	CHECK(result == expected);

	std::istringstream input2("");
	result  = CalculateWordOccurrence(input2);
	expected.clear();
	CHECK(result == expected);

}
TEST_CASE("UpdateWordFrequency() Update word frequency")
{
	std::map<std::string, int> result = { { "cat", 1 }, { "banana", 2 }, { "dog", 1 } };
	std::map<std::string, int> expected = { { "cat", 2 }, { "banana", 2 }, { "dog", 1 } };
	CHECK(result != expected);
	UpdateWordFrequency("cat", result);
	CHECK(result == expected);
}