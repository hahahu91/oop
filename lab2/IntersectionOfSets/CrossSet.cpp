#include "pch.h"
#include <vector>

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
	std::vector<int> v_intersection;
	std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(v_intersection));

	return vectorToSet(v_intersection);
}