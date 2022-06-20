#include "pch.h"
#include "CStudent.h"

CStudent::CStudent(const std::string& name, const std::string& surname, const std::string& patronymic, size_t age)
	: name(name)
	, surname(surname)
	, age(age)
{

	if (name == "" || name == " " || surname == "" || surname == " ")
	{
		throw std::invalid_argument("name and surname cannot be empty\n");
	}
	if (age < 14 || age > 60)
	{
		throw std::out_of_range("age must be between 14 and 60 years old\n");
	}
	(patronymic != " ") ? CStudent::patronymic = patronymic : CStudent::patronymic = "";
};

std::string CStudent::GetName() const
{
	return name;
};

std::string CStudent::GetSurname() const
{
	return surname;
};
std::string CStudent::GetPatronymic() const
{
	return patronymic;
};
size_t CStudent::GetAge() const
{
	return age;
};
bool CStudent::Rename(const std::string& newName, const std::string& newSurname, const std::string& newPatronymic)
{
	if (newName == "" || newName == " " || newSurname == "" || newSurname == " ")
	{
		throw std::invalid_argument("name and surname cannot be empty\n");
		return false;
	}
	name = newName;
	surname = newSurname;

	patronymic = (newPatronymic == " ") ? "" : newPatronymic;

	return true;
};
bool CStudent::SetAge(const size_t newAge)
{
	// вынести константы
	if (newAge < 14 || newAge > 60)
	{
		throw std::out_of_range("age must be between 14 and 60 years old\n");
		return false;
	}
	if (newAge < age)
	{
		throw std::domain_error("new age can not be less\n");
		return false;
	}
	age = newAge;
	return true;
};