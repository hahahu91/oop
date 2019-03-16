#include "pch.h"
#include <iterator>
#include <iomanip>
#include <algorithm>
#include "MultByMinElement.h"
#include "ReadFileWithDoubleNumbers.h"

using namespace std;

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
