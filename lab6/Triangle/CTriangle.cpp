#include "pch.h"
#include "CTriangle.h"
#include <math.h>
#include <stdexcept>

CTriangle::CTriangle(double side1, double side2, double side3)
	: side1(side1)
	, side2(side2)
	, side3(side3)
{
	if (side1 < 0 || side2 < 0 || side3 < 0)
	{
		throw std::invalid_argument("the lengths of the sides of the triangle cannot be negative\n");
	}

	if ((side1 > (side2 + side3))
		|| (side2 > (side1 + side3))
		|| (side3 > (side1 + side2)))
	{
		throw std::domain_error("In a triangle, the length of each side must be less than the sum of the two other sides\n");
	}
}

double CTriangle::GetSide1() const
{
	return side1;
}
double CTriangle::GetSide2() const
{
	return side2;
}
double CTriangle::GetSide3() const
{
	return side3;
}
double CTriangle::GetPerimeter() const
{
	return (side1 + side2 + side3);
}
double CTriangle::GetArea() const
{
	double p = GetPerimeter() / 2;
	return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}