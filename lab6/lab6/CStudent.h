#pragma once
class CStudent
{
public:
	CStudent(const std::string &name, const std::string &surname, const std::string &patronymic, size_t age);
	std::string GetName() const;
	std::string GetSurname() const;
	std::string GetPatronymic() const;
	size_t GetAge() const;
	bool Rename(const std::string& name, const std::string& surname, const std::string& patronymic);
	bool SetAge(const size_t age);

private:
	std::string name;
	std::string surname;
	std::string patronymic;
	size_t age;
};
