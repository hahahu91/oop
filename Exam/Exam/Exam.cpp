#include "pch.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <list>

using namespace std;

template <class InputIt, class T>
int CountIf(InputIt first, InputIt last, const T& pred)
{
	int count = 0;
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			count++;
		}
	}

	return count;
}

bool IsEven(int x)
{
	return (x % 2) == 0;
}

enum class Gender
{
	MALE,
	FEMALE,
};

struct Student
{
	string name;
	Gender gender;
};

int main()
{
	/*
	Разработайте шаблонную функцию CountIf(first, last, pred), возвращающую количество элементов 
		в диапазоне [first, last), для которых значение pred истинно.
	first и last - итераторы, задающие начальную и конечную позиции последовательности элементов.
		Диапазон [first, last) включает в себя все элементы между first и last, включая элемент в позиции first,
		и не включая элемент в позиции last
	pred - унарная функция-предикат, аргументом которой является элемент из диапазона
		Функция возвращает значение, которое может быть преобразовано к типу bool
		Функция не должна менять своих аргументов
		В качестве параметра можно передать указатель на функцию, функциональный объект, либо lambda-выражение
	*/

	string fileNames[] = { "Lecture 1.docx", "Report1.xlsx", "Report 2.xlsx", "hometask.cpp" };

	int numberOfExcelFiles = CountIf(begin(fileNames), end(fileNames), [](const string& name) {
		string ext = ".xlsx";
		return (name.length() > ext.length()) && (name.substr(name.length() - ext.length()) == ext);
	});
	assert(numberOfExcelFiles == 2);

	vector<int> numbers = { 3, 8, 17, -4, 16, 24, 5 };
	int evenNumbersCount = CountIf(numbers.begin(), numbers.end(), IsEven);
	assert(evenNumbersCount == 4); // Количество четных чисел

	list<Student> got{
		{ "Джон Сноу", Gender::MALE },
		{ "Тирион Ланистер", Gender::MALE },
		{ "Дайнерис Таргариен", Gender::FEMALE },
		{ "Санса Старк", Gender::FEMALE },
		{ "Нэд Старк", Gender::MALE },
		{ "Серсея Ланистер", Gender::FEMALE },
		{ "Арья Старк", Gender::FEMALE },
		{ "Джофри Баратеон", Gender::MALE },
		{ "Кхал Дрого", Gender::MALE },
	};
	int maleInGoTCount = CountIf(got.begin(), got.end(), [](const Student& person) {
		return person.gender == Gender::MALE;
	});
	assert(maleInGoTCount == 5);
	/*
	Подсчитайте с помощью функции CountIf количество мужчин среди студентов (типа Student),
	содержащихся в контейнер std::list:
		Джон Сноу (м)
		Тирион Ланистер (м)
		Дайнерис Таргариен (ж)
		Санса Старк (ж)
		Нэд Старк (м)
		Серсея Ланистер (ж)
		Арья Старк (ж)
		Джофри Баратеон (м)
		Кхал Дрого (м)
	*/

	return 0;
}