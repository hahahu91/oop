#include "pch.h"
#include "CTriangle.h"
#include "CSolidShape.h"
#include "MathFunctions.h" 

CTriangle::CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, const std::string& outlineColor, const std::string& fillColor)
	: vertex1(vertex1)
	, vertex2(vertex2)
	, vertex3(vertex3)
	, CSolidShape("Triangle", outlineColor, fillColor)
{}

CPoint midPoint(CPoint p1, CPoint p2)
{
	CPoint mid{ (p2.x + p1.x)/2, (p2.y + p1.y)/2 };
	return mid;
}

double CTriangle::GetArea() const
{
	return 0.5 * CutLength(vertex1, vertex3) * CutLength(midPoint(vertex3, vertex1), vertex2);
};

double CTriangle::GetPerimeter() const
{
	return CutLength(vertex1, vertex2) + CutLength(vertex1, vertex3) + CutLength(vertex2, vertex3);
};

void CTriangle::AppendSolidProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2)
		 << "\tVertex1(" << vertex1.x << ", " << vertex1.y << ")" << std::endl
		 << "\tVertex2(" << vertex2.x << ", " << vertex2.y << ")" << std::endl
		 << "\tVertex3(" << vertex3.x << ", " << vertex3.y << ")" << std::endl;
}

CPoint CTriangle::GetVertex1() const
{
	return vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return vertex3;
}

void CTriangle::Draw(ICanvas& canvas)
{
	canvas.DrawLine(vertex1, vertex2, GetOutLineColor());
	canvas.DrawLine(vertex2, vertex3, GetOutLineColor());
	canvas.DrawLine(vertex3, vertex1, GetOutLineColor());

	canvas.FillPolygon({ vertex1, vertex2, vertex3 }, GetFillColor());
}