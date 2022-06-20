#include "pch.h"
#include "lab4/CAction.h"
#include <sstream>

using namespace std;

SCENARIO("check the number of circle arguments")
{
	stringstream input;
	ostringstream output;

	GIVEN("not all arguments")
	{
		WHEN("user enter circle with not all arguments")
		{
			input << "Circle 1.25 3.25";
			CAction action(input, output);

			THEN("it is notified that not all arguments")
			{
				CHECK_THROWS_WITH(action.HandleCommand(), "Incorrect count of arguments!\nUsage: Circle center.x center.y radius [outline color, fill color]\n");
			}
		}
		WHEN("user enter circle with enough arguments")
		{

			CAction action(input, output);
			input << "Circle 1.25 3.25 4\n";
			CHECK(action.HandleCommand());
			input << "Rectangle 4.25 3.25 3 3 ff0000\n";
			CHECK(action.HandleCommand());
			input << "Triangle 0 0 1.25 3.25 5 4 ff0010 76affa\n";
			CHECK(action.HandleCommand());
			input << "LineSegment 0 0 1.25 12.25\n";
			CHECK(action.HandleCommand());

			//action.Info();
			action.PrintShapeWithMinPerimeter();
			action.PrintShapeWithMaxArea();
			string result = "Min perimeter shape:\n"
				"Rectangle:\n"
					"\tArea = 9.00\n"
					"\tPerimeter = 12.00\n"
					"\tOutline color = ff0000\n"
					"\tFill color = ffffff\n"
					"\tLeftTopAngle(4.25, 3.25)\n"
					"\tWidth(3.00)\n"
					"\tHeigth(3.00)\n"
				"Max area shape:\n"				
				"Circle:\n"
					"\tArea = 50.27\n"
					"\tPerimeter = 25.13\n"
					"\tOutline color = 000000\n"
					"\tFill color = ffffff\n"
					"\tCenter(1.25, 3.25)\n"
					"\tRadius(4.00)\n";
				CHECK(output.str() == result);
		}
		WHEN("user input no shapes")
		{
			CAction action(input, output);

			action.PrintShapeWithMinPerimeter();
			action.PrintShapeWithMaxArea();
			CHECK(output.str() == "");
		}
	}
}