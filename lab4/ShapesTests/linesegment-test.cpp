#include "pch.h"
#include "lab4/LineSegment.h"

bool IsEqual(double const first, double const second)
{
	static double eps = 1e-5;

	return fabs(first - second) < eps;
}

SCENARIO("LineSegment")
{
	GIVEN("2 points and color")
	{
		CPoint startPoint = { 0.0, 1.0 };
		CPoint endPoint = { 2.0, 3.0 };

		WHEN("2 points, no color")
		{
			std::string outlineColor;
			CLineSegment lineSegment(startPoint, endPoint, outlineColor);
			THEN("GetArea")
			{
				CHECK(lineSegment.GetArea() == 0.0);
			}
			AND_THEN("GetPerimeter")
			{
				CHECK(IsEqual(lineSegment.GetPerimeter(), 2.82843));
			}
			AND_THEN("GetStartPoint")
			{
				CHECK(lineSegment.GetStartPoint().x == 0.0);
				CHECK(lineSegment.GetStartPoint().y == 1.0);
			}
			AND_THEN("GetEndPoint")
			{
				CHECK(lineSegment.GetEndPoint().x == 2.0);
				CHECK(lineSegment.GetEndPoint().y == 3.0);
			}
			AND_THEN("GetOutLineColor")
			{
				CHECK(lineSegment.GetOutLineColor() == 000000);
			}
		}
	}
}