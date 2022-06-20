#include "pch.h"
#include "Triangle/CTriangle.h"
#include <sstream>

TEST_CASE("triangle can return yourself sides, perimeter and area")
{
	CTriangle t(4, 5, 6);
	CHECK(t.GetSide1() == 4);
	CHECK(t.GetSide2() == 5);
	CHECK(t.GetSide3() == 6);
	CHECK(t.GetPerimeter() == 15);
	CHECK(t.GetArea() - 9.9215674164 <= 0.0001);
}
TEST_CASE("triangle must throw an exception if the input is incorrect")
{	
	CHECK_THROWS_WITH(CTriangle(4, 5, 10), "In a triangle, the length of each side must be less than the sum of the two other sides\n");
	CHECK_THROWS_WITH(CTriangle(4, -5, 6), "the lengths of the sides of the triangle cannot be negative\n");	
}