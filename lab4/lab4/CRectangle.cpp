#include "pch.h"
#include "CRectangle.h"
#include "CSolidShape.h"

CRectangle::CRectangle(
	CPoint const& leftTopAngle, double const& width, double const& height,
	std::string& outlineColor, std::string& fillColor)
	: leftTopAngle(leftTopAngle)
	, width(width)
	, height(height)
	, CSolidShape("Rectangle", outlineColor, fillColor)
{}

double CRectangle::GetArea() const
{
	return height * width;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (width + height);
}

CPoint CRectangle::GetLeftTop() const
{
	return leftTopAngle;
};

CPoint CRectangle::GetRightBottom() const
{
	return { leftTopAngle.x + width, leftTopAngle.y + height };
}
double CRectangle::GetWidth() const
{
	return width;
};
double CRectangle::GetHeight() const
{
	return height;
}

void CRectangle::AppendSolidProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2)
		 << "\tLeftTopAngle(" << leftTopAngle.x << ", " << leftTopAngle.y << ")" << std::endl
		 << "\tWidth(" << width << ")" << std::endl
		 << "\tHeigth(" << height << ")" << std::endl;
};