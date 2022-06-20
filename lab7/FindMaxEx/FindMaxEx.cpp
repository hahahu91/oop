// Lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

template <typename T>
bool IsLess(const T& lhs, const T& rhs)
{
	return (lhs < rhs);
}
template <class T>

class Comparator
{
public:
	bool operator()(T const& a, T const& b) const
	{
		return a < b;
	}
};

template <typename T, typename Less = std::less<>>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const less = Less())
{
	auto iter = arr.cbegin();
	if (iter == arr.cend())
	{
		return false;
	};

	auto maxItee = iter;

	for (; iter != arr.cend(); ++iter)
	{
		if (less(*maxItee, *iter))
		{
			maxItee = iter;
		}
	}
	maxValue = *maxItee;
	return true;
}


struct Student
{
	std::string name;
	size_t height, weight = 0;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	std::vector<int> v{ 1, 19, 2, 4, 5, 7 };
	int max;
	if (FindMaxEx(v, max))
	{
		std::cout << "Max is " << max << "!\n";
	}

	std::vector<std::string> fileNames = { "Lecture 1.docx", "2222222Report1.xlsx", "2222222Report2.xlsx", "hometask.cpp" };
	std::string maxFileName;
	FindMaxEx(fileNames, maxFileName, [](const std::string& name1, const std::string& name2) {
		return (name1.c_str() < name2.c_str());
	});
	std::cout << "MaxName is " << maxFileName.c_str() << "!\n";

	std::vector<Student> students{
		{ "Джон Сноу", 65, 180 },
		{ "Тирион Ланистер", 50, 102 },
		{ "Дайнерис Таргариен", 48, 160 },
		{ "Санса Старк", 50, 170 },
		{ "Нэд Старк", 98, 182 },
		{ "Серсея Ланистер", 55, 165 },
		{ "Арья Старк", 32, 150 },
		{ "Джофри Баратеон", 35, 162 },
		{ "Кхал Дрого", 105, 195 }
	};
	Student tallest, heaviest;
	FindMaxEx(students, tallest, [](const Student& student1, const Student& student2) {
		return (student1.height < student2.height);
	});
	std::cout << "tallest is " << tallest.name.c_str() << "!\n";

	FindMaxEx(students, heaviest, [](const Student& student1, const Student& student2) {
		return (student1.weight < student2.weight);
	});
	std::cout << "heaviest is " << tallest.name.c_str() << "!\n"; 
}