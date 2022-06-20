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
	������������ ��������� ������� CountIf(first, last, pred), ������������ ���������� ��������� 
		� ��������� [first, last), ��� ������� �������� pred �������.
	first � last - ���������, �������� ��������� � �������� ������� ������������������ ���������.
		�������� [first, last) �������� � ���� ��� �������� ����� first � last, ������� ������� � ������� first,
		� �� ������� ������� � ������� last
	pred - ������� �������-��������, ���������� ������� �������� ������� �� ���������
		������� ���������� ��������, ������� ����� ���� ������������� � ���� bool
		������� �� ������ ������ ����� ����������
		� �������� ��������� ����� �������� ��������� �� �������, �������������� ������, ���� lambda-���������
	*/

	string fileNames[] = { "Lecture 1.docx", "Report1.xlsx", "Report 2.xlsx", "hometask.cpp" };

	int numberOfExcelFiles = CountIf(begin(fileNames), end(fileNames), [](const string& name) {
		string ext = ".xlsx";
		return (name.length() > ext.length()) && (name.substr(name.length() - ext.length()) == ext);
	});
	assert(numberOfExcelFiles == 2);

	vector<int> numbers = { 3, 8, 17, -4, 16, 24, 5 };
	int evenNumbersCount = CountIf(numbers.begin(), numbers.end(), IsEven);
	assert(evenNumbersCount == 4); // ���������� ������ �����

	list<Student> got{
		{ "���� ����", Gender::MALE },
		{ "������ ��������", Gender::MALE },
		{ "�������� ���������", Gender::FEMALE },
		{ "����� �����", Gender::FEMALE },
		{ "��� �����", Gender::MALE },
		{ "������ ��������", Gender::FEMALE },
		{ "���� �����", Gender::FEMALE },
		{ "������ ��������", Gender::MALE },
		{ "���� �����", Gender::MALE },
	};
	int maleInGoTCount = CountIf(got.begin(), got.end(), [](const Student& person) {
		return person.gender == Gender::MALE;
	});
	assert(maleInGoTCount == 5);
	/*
	����������� � ������� ������� CountIf ���������� ������ ����� ��������� (���� Student),
	������������ � ��������� std::list:
		���� ���� (�)
		������ �������� (�)
		�������� ��������� (�)
		����� ����� (�)
		��� ����� (�)
		������ �������� (�)
		���� ����� (�)
		������ �������� (�)
		���� ����� (�)
	*/

	return 0;
}