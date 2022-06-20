#include "pch.h"
#include "lab4/CRectangle.h"

TEST_CASE("The area of a rectangle product height on width")
{
	CPoint leftTopAngle = { 4.0, 0.0 };
	std::string outlineColor;
	CRectangle rectangle(leftTopAngle, 4, 3, outlineColor, outlineColor);
	CHECK(rectangle.GetArea() == 12.0);
}
TEST_CASE("The perimeter of a rectangle is equal to the sum of its sides.")
{
	CPoint leftTopAngle{ 4.0, 0.0 };
	std::string outlineColor;
	CRectangle rectangle(leftTopAngle, 3, 4, outlineColor, outlineColor);
	CHECK(rectangle.GetPerimeter() == 14.0);
}

TEST_CASE("The rectangle has the coordinates leftTopAngle, width and height")
{
	CPoint leftTopAngle = { 4.0, 0.0 };
	double width{ 4 }, heigth{ 3 };
	std::string color;
	CRectangle rectangle(leftTopAngle, width, heigth, color, color);

	CHECK(rectangle.GetLeftTop().x == leftTopAngle.x);
	CHECK(rectangle.GetLeftTop().y == leftTopAngle.y);
	CHECK(rectangle.GetHeight() == heigth);
	CHECK(rectangle.GetWidth() == width);
}

TEST_CASE("The rectangle can display information about yourself")
{
	CPoint leftTopAngle = { 4.0, 0.0 };
	double width{ 4 }, heigth{ 3 };
	std::string color;
	CRectangle rectangle(leftTopAngle, width, heigth, color, color);

	auto str1 = "Rectangle:\n"
				"\tArea = 12.00\n"
				"\tPerimeter = 14.00\n"
				"\tOutline color = 000000\n"
				"\tFill color = 000000\n"
				"\tLeftTopAngle(4.00, 0.00)\n"
				"\tWidth(4.00)\n"
				"\tHeigth(3.00)\n";
	CHECK(rectangle.ToString() == str1);
}
