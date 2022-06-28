#include "pch.h"
#include "lab4/CCircle.h"
#include "lab4/MathFunctions.h"
#include "CMockedCanvas.h"

TEST_CASE("The area of a circle is equal PI on radius squared")
{
	CPoint center = { 5.0, 5.0 };
	std::string outlineColor;
	CCircle circle(center, 5, outlineColor, outlineColor);
	CHECK(IsEqual(circle.GetArea(), 78.5398163397));
}
TEST_CASE("The perimeter of the circle is equal to the product of the radius of 2 PI")
{
	CPoint center = { 5.0, 5.0 };
	std::string outlineColor;
	CCircle circle(center, 5, outlineColor, outlineColor);
	CHECK(IsEqual(circle.GetPerimeter(), 31.4159265359));
}

TEST_CASE("The rectangle has the coordinates center and radius")
{
	CPoint center = { 5.0, 5.0 };
	std::string outlineColor;
	double radius = 5.0;
	CCircle circle(center, radius, outlineColor, outlineColor);

	CHECK(circle.GetCenter().x == center.x);
	CHECK(circle.GetCenter().y == center.y);
	CHECK(circle.GetRadius() == 5.00);
}

TEST_CASE("The circle can display information about yourself")
{
	CPoint center = { 5.0, 5.0 };
	std::string outlineColor;
	double radius = 5.0;
	CCircle circle(center, radius, outlineColor, outlineColor);

	auto str1 = "Circle:\n"
				"\tArea = 78.54\n"
				"\tPerimeter = 31.42\n"
				"\tOutline color = 000000\n"
				"\tFill color = 000000\n"
				"\tCenter(5.00, 5.00)\n"
				"\tRadius(5.00)\n";
	CHECK(circle.ToString() == str1);
}
TEST_CASE("figure drawing")
{
	CMockedCanvas canvas;
	CPoint center = { 5.0, 5.0 };
	std::string outlineColor;
	CCircle circle(center, 5, outlineColor, outlineColor);
	circle.Draw(canvas);

	std::vector<std::string> result = canvas.GetFigureElements();
	CHECK(result.size() == 2);
	CHECK(result.at(0) == "FillCircle");
	CHECK(result.at(1) == "DrawCircle");
}