#include "pch.h"

void MultByMinElement(std::vector<double>& v)
{
	if (!v.empty())
	{
		std::vector <double> ::iterator min = std::min_element(v.begin(), v.end());
		double minElem = *min;
		std::transform(v.begin(), v.end(), v.begin(), [minElem](double x) { return x * minElem; });
	}	
}