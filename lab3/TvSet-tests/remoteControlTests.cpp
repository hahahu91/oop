#include "pch.h"

#include "TvSet/RemoteControl.h"
#include "TvSet/TVSet.h"
#include <sstream>

SCENARIO("Remote control can turn on a TV", "[remote]")
{
	GIVEN("A remote control connected to the TV which is turned off")
	{
		CTVSet tv;
		std::stringstream input, output;
		CRemoteControl rc(tv, input, output);

		REQUIRE(!tv.IsTurnedOn());

		WHEN("user enters TurnOn command")
		{
			input << "TurnOn";
			CHECK(rc.HandleCommand());
			THEN("tv switches on")
			{
				CHECK(tv.IsTurnedOn());
				AND_THEN("user gets notification")
				{
					CHECK(output.str() == "TV is turned on\n");
				}
			}
		}
	}
}

SCENARIO("Remote control provides information about TV", "[remote]")
{
	CTVSet tv;
	std::stringstream input;
	std::ostringstream output;
	input << "Info";
	CRemoteControl rc(tv, input, output);
	GIVEN("A turned off TV")
	{
		REQUIRE(!tv.IsTurnedOn());
		WHEN("user enter Info command")
		{
			rc.HandleCommand();
			THEN("it is notified that TV is off")
			{
				CHECK(output.str() == "TV is turned off\n");
			}
		}
	}

	GIVEN("A turned on TV")
	{
		tv.TurnOn();
		tv.SelectChannel(17);
		REQUIRE(tv.IsTurnedOn());
		WHEN("user enter Info command")
		{
			CHECK(rc.HandleCommand());
			THEN("it is notified that TV is on the current channel")
			{
				CHECK(output.str() == "TV is turned on\nChannel is: 17\n");
			}
		}
	}
}

SCENARIO("Remote control switches channels")
{
	GIVEN("A remote control connected to the TV")
	{
		CTVSet tv;
		std::stringstream input, output;
		CRemoteControl rc(tv, input, output);
		WHEN("TV is turned On")
		{
			tv.TurnOn();
			REQUIRE(tv.IsTurnedOn());
			input << "SelectChannel 42";
			WHEN("user enter SelectChannel command")
			{
				CHECK(rc.HandleCommand());
				THEN("TV switches channel")
				{
					CHECK(tv.GetChannel() == 42);
					AND_THEN("it is notified that TV switches channel")
					{
						CHECK(output.str() == "Channel changed to 42\n");
					}
				}
			}
		}
		WHEN("TV is turned Off")
		{
			REQUIRE(!tv.IsTurnedOn());
			input << "SelectChannel 42";
			WHEN("user enter SelectChannel command")
			{
				CHECK(rc.HandleCommand());
				THEN("TV not switches channel on turned off TV")
				{
					CHECK(tv.GetChannel() == 0);
					AND_THEN("it is notified that TV not switches channel on turned off TV")
					{
						CHECK(output.str() == "Turned off TV not switches channel\n");
					}
				}
			}
		}

	}
}