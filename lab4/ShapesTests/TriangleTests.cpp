#include "pch.h"
#include "lab4/CTriangle.h"
#include "CMockedCanvas.h"

TEST_CASE("The area of a triangle is equal to the product of the half of the base of the triangle and its height")
{
	CPoint vertex1 = { 0.0, 0.0 };
	CPoint vertex2 = { 2.0, 2.0 };
	CPoint vertex3 = { 0.0, 4.0 };
	std::string outlineColor;
	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, outlineColor);
	CHECK(triangle.GetArea() == 4.0);
}
TEST_CASE("The perimeter of a triangle is equal to the sum of its sides.")
{
	CPoint vertex1 = { 0.0, 0.0 };
	CPoint vertex2 = { 4.0, 3.0 };
	CPoint vertex3 = { 0.0, 3.0 };

	std::string outlineColor;
	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, outlineColor);
	CHECK(triangle.GetPerimeter() == 12.0);
}

TEST_CASE("The triangle has the coordinates vertices")
{
	CPoint v1 = { 0.0, 0.0 };
	CPoint v2 = { 3.0, 3.0 };
	CPoint v3 = { 0.0, 3.0 };
	std::string color;
	CTriangle triangle(v1, v2, v3, color, color);

	CHECK(triangle.GetVertex1().x == v1.x);
	CHECK(triangle.GetVertex1().y == v1.y);
	CHECK(triangle.GetVertex2().x == v2.x);
	CHECK(triangle.GetVertex2().y == v2.y);
	CHECK(triangle.GetVertex3().x == v3.x);
	CHECK(triangle.GetVertex3().y == v3.y);
}

TEST_CASE("The triangle can display information about yourself")
{
	CPoint vertex1 = { 0.0, 0.0 };
	CPoint vertex2 = { 4.0, 3.0 };
	CPoint vertex3 = { 0.0, 3.0 };
	std::string color;
	CTriangle triangle(vertex1, vertex2, vertex3, color, color);
	auto str1 = "Triangle:\n"
			"\tArea = 6.41\n"
			"\tPerimeter = 12.00\n"
			"\tOutline color = 000000\n"
			"\tFill color = 000000\n"
			"\tVertex1(0.00, 0.00)\n"
			"\tVertex2(4.00, 3.00)\n"
			"\tVertex3(0.00, 3.00)\n";
	CHECK(triangle.ToString() == str1);
}

TEST_CASE("Triangle drawing")
{
	CPoint vertex1 = { 0.0, 0.0 };
	CPoint vertex2 = { 4.0, 3.0 };
	CPoint vertex3 = { 0.0, 3.0 };
	std::string color;
	CTriangle triangle(vertex1, vertex2, vertex3, color, color);
	CMockedCanvas canvas;
	triangle.Draw(canvas);

	std::vector<std::string> result = canvas.GetFigureElements();
	CHECK(result.size() == 4);
	CHECK(result.at(0) == "DrawLine");
	CHECK(result.at(1) == "DrawLine");
	CHECK(result.at(2) == "DrawLine");
	CHECK(result.at(3) == "FillPolygon");
}
