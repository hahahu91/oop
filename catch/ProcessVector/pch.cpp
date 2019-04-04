

#include "pch.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

#define EPSILON 0.0001

using namespace std;

bool AreSame(double a, double b)
{
	return fabs(a - b) < EPSILON;
}

bool ReadFileWithDoubleNumbers(const string& fileName, vector<double>& v)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Failed to open file for reading\n";
		return false;
	}
	double number = 0;

	while (file >> number)
	{
		v.push_back(number);
	}

	if (!file.eof())
	{
		cout << "Reading error\n";
		return false;
	}
	return true;
}

void MultByMinElement(vector<double>& v)
{
	double min = v[0];
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i] < min)
		{
			min = v[i];
		}
	}
	for (size_t i = 0; i < v.size(); i++)
	{
		v[i] *= min;
		if (AreSame(v[i], 0))
			v[i] = 0;
	}
}

void PrintDoubleVector(const vector<double>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << setprecision(9) << v[i];
		if (i != v.size() - 1)
		{
			cout << " ";
		}
	}
	cout << "\n";
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: processvector.exe <file>\n";
		return 1;
	}

	vector<double> numbers;
	if (ReadFileWithDoubleNumbers(argv[1], numbers))
	{
		if (numbers.size() > 0)
		{
			MultByMinElement(numbers);
			sort(numbers.begin(), numbers.end());
			PrintDoubleVector(numbers);
		}

		return 0;
	}
	else
	{
		return 1;
	}
}
