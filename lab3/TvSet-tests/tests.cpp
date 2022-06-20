#include "pch.h"
#include "TvSet/TVSet.h"

SCENARIO("TVSet can be turned on and off")
{
	GIVEN("A turned off TV")
	{
		CTVSet tv;
		REQUIRE(!tv.IsTurnedOn());

		WHEN("tv is turned on")
		{
			tv.TurnOn();
			THEN("it becomes turned on")
			{
				CHECK(tv.IsTurnedOn());
			}
		}

		AND_WHEN("tv is turned off")
		{
			tv.TurnOff();
			THEN("it becomes turned off")
			{
				CHECK(!tv.IsTurnedOn());
			}
		}
	}
}

SCENARIO("TVSet first turnOn is at channel 1")
{
	CTVSet tv;
	tv.TurnOn();
	CHECK(tv.GetChannel() == 1);
}

SCENARIO("A turned on TV can select channel from 1 to 99")
{
	GIVEN("A TV")
	{
		CTVSet tv;
		WHEN("tv is turned on")
		{
			tv.TurnOn();
			tv.SelectChannel(42);
			THEN("It can select channels from 1 to 99")
			{
				CHECK(tv.SelectChannel(1));
				CHECK(tv.GetChannel() == 1);

				CHECK(tv.SelectChannel(99));
				CHECK(tv.GetChannel() == 99);

				// ¬ыбираем канал между 1 и 99
				CHECK(tv.SelectChannel(42));
				CHECK(tv.GetChannel() == 42);
			}
			// ѕри попытке выбрать канал за пределами [1; 99]
			// телевизор не должен мен€ть свой канал
			AND_WHEN("TV can't select a channel beyond the 1..99 range")
			{
				SECTION("can't select channel less than 1")
				{
					CHECK(!tv.SelectChannel(0));
					CHECK(tv.GetChannel() == 42);
				}
				SECTION("can't select channel greater than 99")
				{
					CHECK(!tv.SelectChannel(100));
					CHECK(tv.GetChannel() == 42);
				}
			}
		}
	}
}

SCENARIO("A turned off TV can't select channels")
{
	GIVEN("A TV")
	{
		CTVSet tv;
		WHEN("it is Turned Off")
		{
			THEN("It is at channel 0")
			{
				CHECK(tv.GetChannel() == 0);
			}
			THEN("It can't select channels")
			{
				CHECK(!tv.SelectChannel(87));
				CHECK(tv.GetChannel() == 0);
			}
			THEN("It can't select prevchannel")
			{
				CHECK(!tv.SelectPreviousChannel());
				CHECK(tv.GetChannel() == 0);
			}
			THEN("It can't set channel name")
			{
				CHECK(!tv.SetChannelName(1, "ORT"));
				CHECK(tv.GetChannel() == 0);
			}
			THEN("It can't get channel name")
			{
				CHECK(tv.GetChannelName(1) == "");
				CHECK(tv.GetChannel() == 0);
			}
		}
	}
}

SCENARIO("A TV must restore the previously selected channel")
{
	GIVEN("A TV with selected channel")
	{
		CTVSet tv;
		tv.TurnOn();
		tv.SelectChannel(42);
		WHEN("TV is turned off and on")
		{
			tv.TurnOff();
			tv.TurnOn();
			THEN("restores last selected channel")
			{
				CHECK(tv.GetChannel() == 42);
			}
		}
	}
}
SCENARIO("TV saves the previous channel")
{
	GIVEN("A TV is turned on")
	{
		CTVSet tv;
		tv.TurnOn();
		WHEN("You switch the channel, you can return to the previous channel")
		{
			tv.SelectChannel(2);
			tv.SelectChannel(3);
			tv.SelectPreviousChannel();
			THEN("restores previous channel")
			{
				CHECK(tv.GetChannel() == 2);
				AND_THEN("you can come back again")
				{
					tv.SelectPreviousChannel();
					CHECK(tv.GetChannel() == 3);
				}
			}
		}
		THEN("The selection of the previous channel does not change the selected channel.")
		{
			tv.SelectPreviousChannel();
			CHECK(tv.GetChannel() == 1);
		}
		WHEN("turning the TV off and on, the previous channel is saved")
		{
			tv.SelectChannel(2);
			tv.SelectChannel(3);
			tv.TurnOff();
			tv.TurnOn();
			tv.SelectPreviousChannel();
			THEN("restores previous channel")
			{
				CHECK(tv.GetChannel() == 2);
			}
		}
	}
}
SCENARIO("You can SetChannelName")
{
	GIVEN("Turned on TV")
	{
		CTVSet tv;
		tv.TurnOn();
		WHEN("You set channel name")
		{
			CHECK(tv.SetChannelName(1, "ORT"));
			THEN("calling getChannelName you get its name")
			{
				CHECK(tv.GetChannelName(1) == "ORT");
			}
			THEN("calling getChannelByName you get its number")
			{
				(tv.GetChannelByName("ORT") == 1);
			}
		}
		WHEN("You set channel name with blanks")
		{
			CHECK(tv.SetChannelName(3, " ORT  THREE "));
			THEN("calling getChannelName you get its name without extra blanks")
			{
				CHECK(tv.GetChannelName(3) == "ORT THREE");
			}
		}
	}
}
SCENARIO("You can Select Channel By Name")
{
	GIVEN("Turned on TV with set channel name")
	{
		CTVSet tv;
		tv.TurnOn();
		tv.SetChannelName(3, "TNT");
		WHEN("You select channel by selectChannel(Name)")
		{
			CHECK(tv.SelectChannel("TNT"));
			THEN("Tv select channel")
			{
				CHECK(tv.GetChannel() == 3);
			}
		}
	}
}
SCENARIO("If the name has already been assigned to another channel, then there is a change of association")
{
	GIVEN("Turned On TV with set channel Name")
	{
		CTVSet tv;
		tv.TurnOn();
		tv.SetChannelName(3, "TNT");
		WHEN("We set the same name to another channel")
		{
			CHECK(tv.SetChannelName(4, "TNT"));
			THEN("there is a change of association")
			{
				CHECK(tv.GetChannelByName("TNT") == 4);
				CHECK(tv.GetChannelName(3) != "TNT");
			}
		}
	}
}
/*
	// Ќапишите тесты дл€ недостающего функционала класса CTVSet (если нужно)
	//	и дл€ дополнительных заданий на бонусные баллы (если нужно)
	// ѕосле написани€ каждого теста убедитесь, что он не проходит.
	// ƒоработайте простейшим образом класс CTVSet, чтобы этот тест и предыдущие проходили
	// ѕри необходимости выполните рефакторинг кода, сохран€€ работоспособность тестов
	// ѕри необходимости используйте вложенные тесты (как использующие fixture, так и нет)
	// »мена тестам и test suite-ам давайте такие, чтобы выводима€ в output иерархи€
	//	тестов читалась как спецификаци€ на английском €зыке, описывающа€ поведение телевизора
	*/
