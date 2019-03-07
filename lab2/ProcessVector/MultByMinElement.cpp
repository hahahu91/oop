#include "pch.h"
#define EPSILON 0.0001

bool AreSame(double a, double b)
{
	return fabs(a - b) < EPSILON;
}

void MultByMinElement(std::vector<double>& v)
{
	double min = v[0];
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i] < min)
		{
			min = v[i];
		}
	}
	for (size_t i = 0; i < v.size(); i++)
	{
		v[i] *= min;
		if (AreSame(v[i], 0))
			v[i] = 0;
	}
}