// Lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>

template <typename T>
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	auto iter = arr.cbegin();
	if (iter == arr.cend())
	{
		return false;
	};
	auto maxItee = iter;

	for (; iter != arr.cend(); ++iter)
	{
		if (*maxItee < *iter)
		{
			maxItee = iter;
		}
	}
	maxValue = *maxItee;
	return true;
}

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
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

template <>
bool FindMax<const char*>(std::vector<const char*> const& arr, const char*& maxValue)
{
	auto iter = arr.cbegin();
	if (iter == arr.cend())
	{
		return false;
	};
	auto maxItee = iter;

	for (; iter != arr.cend(); ++iter)
	{
		if (strcmp(*maxItee, *iter) > 0)
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
	size_t height, weight;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	std::vector<int> v{ 1, 19, 2, 4, 5, 7 };
	int max;
	if (FindMax(v, max))
	{
		std::cout << "Max is " << max << "!\n";
	}

	std::vector<std::string> fileNames = { "Lecture 1.docx", "2222222Report1.xlsx", "2222222Report2.xlsx", "hometask.cpp" };
	std::string maxFileName;
	FindMax(fileNames, maxFileName, [](const std::string& name1, const std::string& name2) {
		return (name1.c_str() < name2.c_str());
	});
	std::cout << "MaxName is " << maxFileName.c_str() << "!\n";

	std::vector<Student> students{
		{ "???? ????", 65, 180 },
		{ "?????? ????????", 50, 102 },
		{ "???????? ?????????", 48, 160 },
		{ "????? ?????", 50, 170 },
		{ "??? ?????", 98, 182 },
		{ "?????? ????????", 55, 165 },
		{ "???? ?????", 32, 150 },
		{ "?????? ????????", 35, 162 },
		{ "???? ?????", 105, 195 }
	};
	Student tallest, heaviest;
	FindMax(students, tallest, [](const Student& student1, const Student& student2) {
		return (student1.height < student2.height);
	});
	std::cout << "tallest is " << tallest.name.c_str() << "!\n";
	FindMax(students, heaviest, [](const Student& student1, const Student& student2) {
		return (student1.weight < student2.weight);
	});
	std::cout << "heaviest is " << tallest.name.c_str() << "!\n";

	std::vector<const char*> fileNames2 = { "Lecture 1.docx", "2222222Report1.xlsx", "2222222Report2.xlsx", "hometask.cpp" };
	//FindMax(fileNames2, maxFileName);
	//std::cout << "MaxName is " << maxFileName.c_str() << "!\n";


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
