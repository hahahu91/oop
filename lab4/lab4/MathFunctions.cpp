#include "pch.h"
#include "MathFunctions.h"


double CutLength(CPoint const& startPoint, CPoint const& endPoint)
{
	return sqrt(pow((startPoint.y - endPoint.y), 2) + pow((startPoint.x - endPoint.x), 2));
}

bool IsEqual(double const first, double const second)
{
	static double eps = 1e-5;

	return fabs(first - second) < eps;
}