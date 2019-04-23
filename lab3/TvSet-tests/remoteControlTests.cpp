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
			WHEN("user enter SelectChannel command")
			{
				input << "SelectChannel 42";
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
			AND_WHEN("user enter unselected channel command")
			{
				input << "SelectChannel 100";
				CHECK(!rc.HandleCommand());
				THEN("TV not switch channel")
				{
					CHECK(tv.GetChannel() == 1);
					AND_THEN("it is notified that TV not switch channel")
					{
						CHECK(output.str() == "Channel can not change to 100\n");
					}
				}
			}
		}
		WHEN("TV is turned Off")
		{
			REQUIRE(!tv.IsTurnedOn());
			input << "SelectChannel 42";
			AND_WHEN("user enter SelectChannel command")
			{
				CHECK(!rc.HandleCommand());
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
SCENARIO("Remote control can use previous channel")
{
	GIVEN("Turned on TV and selected channel")
	{
		CTVSet tv;
		std::stringstream input, output;
		CRemoteControl rc(tv, input, output);
		tv.TurnOn();
		tv.SelectChannel(42);
		input << "SelectPreviousChannel";
		WHEN("user input command SelectPreviousChannel")
		{
			CHECK(rc.HandleCommand());
			THEN("tv switch on previous channel and user is notified")
			{
				CHECK(tv.GetChannel() == 1);
				CHECK(output.str() == "Channel changed to 1\n");
			}
		}

	}
}
SCENARIO("Remote control can set channel Name and get channel by name")
{
	GIVEN("Turned on TV")
	{
		CTVSet tv;
		std::stringstream input, output;
		CRemoteControl rc(tv, input, output);
		tv.TurnOn();
		WHEN("user input command SetChannelName")
		{
			input << "SetChannelName 2 RTR";
			CHECK(rc.HandleCommand());
			THEN("tv set on channel Name and user is notified")
			{
				CHECK(tv.GetChannelByName("RTR") == 2);
				CHECK(output.str() == "Channel 2 set Name RTR\n");
			}
		
		}
		
	}
}

SCENARIO("Remote control can get channel number by name and name by number")
{
	GIVEN("Turned on TV with set channel name")
	{
		CTVSet tv;
		std::stringstream input, output;
		CRemoteControl rc(tv, input, output);
		tv.TurnOn();
		tv.SetChannelName(2, "RTR");
		WHEN("user input command GetChannelName")
		{
			input << "GetChannelName 2";
			CHECK(rc.HandleCommand());
			THEN("tv show channel Name")
			{
				//CHECK(tv.GetChannelName(2) == "RTR");
				CHECK(output.str() == "Channel 2 Name: RTR\n");
			}
		}
		WHEN("user input command GetChannelByName")
		{
			input << "GetChannelByName RTR";
			CHECK(rc.HandleCommand());
			THEN("tv show channel number")
			{
				//CHECK(tv.GetChannelByName("RTR") == 2);
				CHECK(output.str() == "Channel RTR has number: 2\n");
			}
		}
	}
}


	