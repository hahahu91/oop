#include "pch.h"

void MultByMinElement(std::vector<double>& v)
{
	if (!v.empty())
	{
		double minElem = *std::min_element(v.begin(), v.end());
		std::transform(v.begin(), v.end(), v.begin(), [minElem](double x) { return x * minElem; });
	}	
}