#include "pch.h"
#include "lab4/LineSegment.h"
#include "CMockedCanvas.h"

TEST_CASE("the area of the segment is zero")
{
	CPoint startPoint = { 0.0, 0.0 };
	CPoint endPoint = { 3.0, 4.0 };
	std::string outlineColor;
	CLineSegment lineSegment(startPoint, endPoint, outlineColor);

	CHECK(lineSegment.GetArea() == 0.0);
}

TEST_CASE("The perimeter of the segment is equal to its length")
{
	CPoint startPoint = { 0.0, 0.0 };
	CPoint endPoint = { 3.0, 4.0 };
	std::string outlineColor;
	CLineSegment lineSegment(startPoint, endPoint, outlineColor);

	CHECK(lineSegment.GetPerimeter() == 5);
}

TEST_CASE("The segment has the coordinates of the ends")
{
	CPoint startPoint = { 0.0, 0.0 };
	CPoint endPoint = { 3.0, 4.0 };
	std::string outlineColor;
	CLineSegment lineSegment(startPoint, endPoint, outlineColor);

	CHECK(lineSegment.GetStartPoint().x == 0.0);
	CHECK(lineSegment.GetStartPoint().y == 0.0);
	CHECK(lineSegment.GetEndPoint().x == 3.0);
	CHECK(lineSegment.GetEndPoint().y == 4.0);
}

TEST_CASE("line drawing")
{
	CPoint startPoint = { 0.0, 0.0 };
	CPoint endPoint = { 3.0, 4.0 };
	std::string outlineColor;
	CLineSegment line(startPoint, endPoint, outlineColor);

	CMockedCanvas canvas;
	line.Draw(canvas);

	std::vector<std::string> result = canvas.GetFigureElements();
	CHECK(result.size() == 1);
	CHECK(result.at(0) == "DrawLine");
}
