#include "pch.h"
#include <vector>
#include <iterator>

std::set<int> vectorToSet(std::vector<int> v) {
	std::set<int> setOfNum;
	for (int num : v)
	{
		setOfNum.insert(num);
	}
	return setOfNum;
}

std::set<int> CrossSet(std::set<int> const& set1, std::set<int> const& set2)
{	
	std::set<int> intersection;
	std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(intersection, intersection.end()));

	return intersection;
}