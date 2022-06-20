#include "pch.h"
#include "../Car-project/RemoteControlCar.h"
#include "../Car-project/Car.h"
#include <sstream>

SCENARIO("Remote control can Engine on a car", "[remote]")
{
	GIVEN("A remote control connected to the car which is Engine off")
	{
		Car car;
		std::stringstream input, output;
		RemoteControl rc(car, input, output);

		REQUIRE(!car.IsOnEngine());

		WHEN("user enters EngineOn command")
		{
			input << "EngineOn";
			CHECK(rc.HandleCommand());
			THEN("Car engine on")
			{
				CHECK(car.IsOnEngine());
				AND_THEN("user gets notification")
				{
					CHECK(output.str() == "Car engine is on\n");
				}
			}
		}
	}
}

SCENARIO("Remote control can engine off a car", "[remote]")
{
	GIVEN("A remote control connected to the car which is Engine on")
	{
		Car car;
		std::stringstream input, output;
		RemoteControl rc(car, input, output);
		car.TurnOnEngine();
		REQUIRE(car.IsOnEngine());

		WHEN("user enters EngineOff command")
		{
			input << "EngineOff";
			CHECK(rc.HandleCommand());
			THEN("car engine off")
			{
				CHECK(!car.IsOnEngine());
				AND_THEN("user gets notification")
				{
					CHECK(output.str() == "Car engine is off\n");
				}
			}
		}
	}
}

SCENARIO("Remote control can set gear")
{
	GIVEN("A remote control connected to the car")
	{
		Car car;
		std::stringstream input, output;
		RemoteControl rc(car, input, output);
		WHEN("car engine is On")
		{
			car.TurnOnEngine();
			REQUIRE(car.IsOnEngine());
			WHEN("user enter SetGear command")
			{
				car.SetGear(1);
				car.SetSpeed(20);
				input << "SetGear 2";
				CHECK(rc.HandleCommand());
				THEN("car set gear")
				{
					CHECK(car.GetGear() == 2);
					AND_THEN("it is notified that car set gear")
					{
						CHECK(output.str() == "Car set gear to 2\n");
					}
				}
			}
			AND_WHEN("user enter SetGear && if the car cannot switch to this gear")
			{
				car.SetGear(1);
				car.SetSpeed(10);
				input << "SetGear 2";
				CHECK(!rc.HandleCommand());
				THEN("car not set gear")
				{
					CHECK(car.GetGear() == 1);
					AND_THEN("it is notified that car not set this gear")
					{
						CHECK(output.str() == "Car can not set gear to 2\n");
					}
				}
			}
		}
		WHEN("car engine is Off")
		{
			REQUIRE(!car.IsOnEngine());
			input << "SetGear 1";
			AND_WHEN("user enter SetGear command")
			{
				CHECK(!rc.HandleCommand());
				THEN("car not set gear with engine off")
				{
					CHECK(car.GetGear() == 0);
					AND_THEN("it is notified that car not set gear with engine off")
					{
						CHECK(output.str() == "Car with engine is off not set gear\n");
					}
				}
			}
		}
	}
}


SCENARIO("Remote control can use setSpeed")
{
	GIVEN("Car with engine on car && speed not 0")
	{
		Car car;
		std::stringstream input, output;
		RemoteControl rc(car, input, output);
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		WHEN("user input command SetSpeed within the possible at this gear")
		{
			input << "SetSpeed 20";
			CHECK(rc.HandleCommand());
			THEN("car set speed && user is notified")
			{
				CHECK(car.GetSpeed() == 20);
				CHECK(output.str() == "Car set speed 20\n");
			}
		}
		WHEN("user input SetSpeed out of the extent possible on this gear")
		{
			input << "SetSpeed 50";
			CHECK(!rc.HandleCommand());
			THEN("car set speed && user is notified")
			{
				CHECK(car.GetSpeed() == 10);
				CHECK(output.str() == "Car can not set speed 50 on 1 gear\n");
			}
		}
		WHEN("user tries to increase speed with neutral gear")
		{
			car.SetGear(0);

			input << "SetSpeed 50";
			CHECK(!rc.HandleCommand());
			THEN("car can not set speed && user is notified")
			{
				CHECK(car.GetSpeed() == 10);
				CHECK(output.str() == "Car can not set speed 50 on 0 gear\n");
			}
		}
	}
}


SCENARIO("Remote contol can only Engine on the Engine Off car && switch to neutral gear")
{
	GIVEN("EngineOff car")
	{
		Car car;
		std::stringstream input, output;
		RemoteControl rc(car, input, output);
		REQUIRE(!car.IsOnEngine());
		WHEN("You try set not neutral gear on EngineOff car")
		{
			input << "SetGear 1";
			CHECK(!rc.HandleCommand());
			THEN("It can't be done")
			{
				CHECK(car.GetGear() == 0);
				AND_THEN("user gets notification")
				{
					CHECK(output.str() == "Car with engine is off not set gear\n");
				}
			}
		}
		AND_WHEN("You try set neutral gear on EngineOff car")
		{
			CHECK(car.SetGear(0));
			input << "SetGear 0";
			CHECK(rc.HandleCommand());
			THEN("It can be done")
			{
				CHECK(car.GetGear() == 0);
			}
		}
		WHEN("You try SetSpeed")
		{
			input << "SetSpeed 10";
			CHECK(!rc.HandleCommand());
			THEN("It can't be done")
			{
				CHECK(car.GetSpeed() == 0);
				AND_THEN("user gets notification")
				{
					CHECK(output.str() == "Car with engine off not set speed\n");
				}
			}
		}
		WHEN("You try Unknown command")
		{
			input << "set max speed";
			CHECK(!rc.HandleCommand());
			THEN("It can't be done")
			{
				CHECK(car.GetSpeed() == 0);
			}
		}
	}
}

SCENARIO("Remote control provides information about Car", "[remote]")
{
	Car car;
	std::stringstream input;
	std::ostringstream output;
	RemoteControl rc(car, input, output);
	GIVEN("A car with Engine off ")
	{
		REQUIRE(!car.IsOnEngine());
		WHEN("user enter Info command")
		{
			input << "Info";
			CHECK(rc.HandleCommand());
			THEN("it is notified that car is off")
			{
				CHECK(output.str() == "Car engine is off\n");
			}
		}
	}

	GIVEN("A car with engine on")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		REQUIRE(car.IsOnEngine());
		WHEN("user enter Info command")
		{
			input << "Info";
			CHECK(rc.HandleCommand());
			THEN("it is notified")
			{
				CHECK(output.str() == "Car engine is on\nGear is: 1\nSpeed is: 10\n");
			}
		}
	}
}

/*Х
Х	с заднего хода можно переключитьс€ на первую передачу только на нулевой скорости;
*/
SCENARIO("Check reverse gear", "[remote]")
{
	Car car;
	std::stringstream input;
	std::ostringstream output;
	RemoteControl rc(car, input, output);
	car.TurnOnEngine();
	GIVEN("A car with engine is on")
	{
		REQUIRE(car.GetSpeed() == 0);
		WHEN("Speed is 0, the car can set reverse gear")
		{
			input << "SetGear -1";
			CHECK(rc.HandleCommand());
			THEN("it is notified")
			{
				CHECK(output.str() == "Car set gear to -1\n");
			}
		}
		WHEN("Direction is back on neutral gear do not engage reverse gear")
		{
			car.SetGear(-1);
			car.SetSpeed(20);
			car.SetGear(0);
			input << "SetGear -1";
			CHECK(!rc.HandleCommand());
			THEN("it is notified")
			{
				CHECK(output.str() == "Car allow reverse gear only at 0 speed\n");
			}
		}
		WHEN("When direction is back, 1 speed can only be set at 0 speed.")
		{
			car.SetGear(-1);
			car.SetSpeed(20);
			input << "SetGear 1";
			THEN("it is notified")
			{
				CHECK(!rc.HandleCommand());
				CHECK(output.str() == "Car when driving in reverse allow set 1 gear only at 0 speed\n");
			}

			car.SetSpeed(0);
			THEN("it is notified")
			{

				CHECK(rc.HandleCommand());
				CHECK(output.str() == "Car set gear to 1\n");
			}

		}
	}
}