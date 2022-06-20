#include "pch.h"
#include "../Car-project/Car.h"

SCENARIO("Car")
{
	
	GIVEN("A Car with the engine turned off")
	{
		Car car;
		CHECK(!car.IsOnEngine());
		WHEN("Engine is turn off")
		{
			THEN("Can set only neutral gear")
			{
				CHECK(!car.SetGear(1));
				CHECK(!car.SetGear(-1));
				CHECK(car.SetGear(0));

			}
		}

		WHEN("Turn on the engine of the car")
		{
			CHECK(car.TurnOnEngine());
			THEN("it becomes turned on engine with 0 speed neutral gear && direction stand")
			{
				CHECK(car.IsOnEngine());
				CHECK(car.GetGear() == 0);
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetDirection() == Direction::Stand);
			}
			WHEN("the engine is turnOn the car can change gear")
			{
				CHECK(car.IsOnEngine());
				REQUIRE(car.SetGear(1));
				WHEN("The transmission is not neutral can increase the speed")
				{
					CHECK(car.SetSpeed(20));
					THEN("If the speed was within the limits of permissible in this gear")
					{
						CHECK(car.GetSpeed() == 20);
					}
					THEN("If the speed was outside the limits of permissible in this gear")
					{
						CHECK(!car.SetSpeed(40));
						CHECK(car.GetSpeed() == 20);
					}
				}
			}
			
			WHEN("Current speed = 0km can set only 1 gear, neutral && reverse gear")
			{
				REQUIRE(car.IsOnEngine());
				REQUIRE(car.GetSpeed() == 0);
				CHECK(car.SetGear(1));
				AND_WHEN("Current gear is neutral && current speed 0 can turn off the engine")
				{
					CHECK(car.SetGear(0));
					CHECK(car.TurnOffEngine());
					CHECK(car.GetDirection() == Direction::Stand);
					THEN("it becomes turned off")
					{
						CHECK(!car.IsOnEngine());
					}
				}
				AND_WHEN("Current gear is reversed. ")
				{
					CHECK(car.SetGear(-1));
					CHECK(car.SetSpeed(20));
					THEN("Direction is back you can't set 1-5 gear")
					{
						CHECK(car.GetDirection() == Direction::Back);
						CHECK(!car.SetGear(1));

						WHEN("the gear is neutral can set")
						{

							CHECK(car.SetGear(0));
							THEN("Direction is back && gear is neutral not possible set 1-5 gear")
							{
								CHECK(!car.SetGear(1));
								CHECK(!car.SetGear(5));
							}
							THEN("It is not possible to turn on the reserved gear even when moving back not at zero speed")
							{
								CHECK(car.GetSpeed() != 0);
								CHECK(car.GetDirection() == Direction::Back);
								CHECK(car.GetGear() == 0);
								CHECK(!car.SetGear(-1));
							}
						}
					}
					
					THEN("Max speed is 20")
					{
						CHECK(!car.SetSpeed(40));
						CHECK(car.GetSpeed() == 20);
					}
					THEN("1 gear can set only at speed is 0")
					{
						CHECK(car.GetDirection() == Direction::Back);
						CHECK(car.GetSpeed() != 0);
						CHECK(!car.SetGear(1));
						CHECK(car.SetSpeed(0));
						CHECK(car.SetGear(1));
					}
					
				}
			}
		}
		
	}
	
	GIVEN("A car with engine")
	{
		Car car;
		car.TurnOnEngine();
		REQUIRE(car.IsOnEngine());
		WHEN("Neutral gear is possible only set lower speed")
		{
			car.SetGear(-1);
			car.SetSpeed(10);
			CHECK(car.SetGear(0));
			CHECK(!car.SetSpeed(20));
			CHECK(car.SetSpeed(5));
			CHECK(car.GetSpeed() == 5);
			car.SetSpeed(0);
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);
			car.SetSpeed(50);
			car.SetGear(5);
			car.SetSpeed(150);
			CHECK(!car.SetSpeed(151));
			CHECK(car.SetGear(0));
			CHECK(car.SetSpeed(100));
			CHECK(!car.SetSpeed(101));

		}
		WHEN("User try set not correct gear or speed")
		{
			CHECK(!car.SetGear(-2));
			CHECK(!car.SetSpeed(6));
			CHECK(!car.SetSpeed(-1));
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);
			car.SetSpeed(50);
			car.SetGear(5);
			car.SetSpeed(150);
			
			CHECK(!car.SetSpeed(151));
			CHECK(!car.SetSpeed(0));
		}
		
	}
}
SCENARIO("НА скорости заглушить")
{
	GIVEN("Car")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		CHECK(!car.TurnOffEngine());

	}
}
