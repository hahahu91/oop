#pragma once
#include "pch.h"
#include "CCircle.h"
#include "CSolidShape.h"
#define _USE_MATH_DEFINES
#include <math.h>

CCircle::CCircle(CPoint const& center, double const& radius, std::string& outlineColor, std::string& fillColor)
	: center(center)
	, radius(radius)
	, CSolidShape("Circle", outlineColor, fillColor)
{}

double CCircle::GetArea() const
{
	return M_PI * pow(radius, 2);
}
	
double CCircle::GetPerimeter() const
{
	return 2 * M_PI * radius;
}

CPoint CCircle::GetCenter() const
{
	return center;
}

double CCircle::GetRadius() const
{
	return radius;
}

void CCircle::AppendSolidProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2)
		 << "\tCenter(" << center.x << ", " << center.y << ")" << std::endl
		 << "\tRadius(" << radius << ")" << std::endl;
};