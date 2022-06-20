#include "pch.h"
#include "lab6/CStudent.h"

TEST_CASE("CStudent can return yourself name, surname, patronymic and age")
{
	CStudent student("Ivanov", "Ivan", "Ivanovich", 25);
	CHECK(student.GetName() == "Ivanov");
	CHECK(student.GetSurname() == "Ivan");
	CHECK(student.GetPatronymic() == "Ivanovich");
	CHECK(student.GetAge() == 25);
}

SCENARIO("CStudent allows you to change the name and age of the student") {
	GIVEN("Student")
	{
		CStudent student("Ivanov", "Ivan", "Ivanovich", 25);
		WHEN("change name")
		{
			student.Rename("Smirnov", "Artem", "Nikolaevich");
			THEN("the name change")
			{
				CHECK(student.GetName() == "Smirnov");
				CHECK(student.GetSurname() == "Artem");
				CHECK(student.GetPatronymic() == "Nikolaevich");
			}
		}
		WHEN("try to change the name to incorrect data")
		{
			CHECK_THROWS_WITH(student.Rename("Smirnov", " ", "Nikolaevich"), "name and surname cannot be empty\n");
			THEN("the name no change")
			{
				CHECK(student.GetName() == "Ivanov");
				CHECK(student.GetSurname() == "Ivan");
				CHECK(student.GetPatronymic() == "Ivanovich");
			}
		}
		WHEN("change age")
		{
			student.SetAge(28);
			THEN("the age change")
			{
				CHECK(student.GetAge() == 28);
			}
		}
		WHEN("try to change the age to incorrect data")
		{
			CHECK_THROWS_WITH(student.SetAge(12), "age must be between 14 and 60 years old\n");
			THEN("the age no change")
			{
				CHECK(student.GetAge() == 25);
			}
			CHECK_THROWS_WITH(student.SetAge(24), "new age can not be less\n");
			THEN("the age no change")
			{
				CHECK(student.GetAge() == 25);
			}
		}
	}
}

// вынести тесты по возрасту

TEST_CASE("Student should not be created with invalid input")
{
	CStudent student("Smirnov", "Nikolay", " ", 25);
	CHECK(student.GetPatronymic() == "");
}