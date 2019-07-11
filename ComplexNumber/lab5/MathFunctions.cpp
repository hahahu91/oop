#include "pch.h"
#include <math.h>

bool IsEqual(double const first, double const second)
{
	static double eps = 1e-4;

	return fabs(first - second) < eps;
}