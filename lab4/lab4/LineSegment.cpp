#include "pch.h"
//#include "Point.h"
#include <math.h>
#include "LineSegment.h"
#include "CShape.h"
#include "MathFunctions.h"
using namespace std;

CLineSegment::CLineSegment(CPoint const& startPoint, CPoint const& endPoint,const string & outlineColor)
	: startPoint(startPoint)
	, endPoint(endPoint)
	, CShape("LineSegment", outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return CutLength(startPoint, endPoint);
}

CPoint CLineSegment::GetStartPoint() const
{
	return startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return endPoint;
}

void CLineSegment::AppendProperties(std::ostream& strm) const
{
	strm << fixed << setprecision(2) << "\tstart point(" << startPoint.x << ", " << startPoint.y << ")" << endl
		 << "\tend point(" << endPoint.x << ", " << endPoint.y << ")" << endl;
}

void CLineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(startPoint, endPoint, GetOutLineColor());
}