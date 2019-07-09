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
			input << "Circle 1.25 3.25 4";
			CAction action(input, output);

			THEN("it is notified that not all arguments")
			{
				CHECK(action.HandleCommand());
				action.Info();
				CHECK(output);
			}
		}
	}
}