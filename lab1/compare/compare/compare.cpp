// compare.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: compare.exe <file1> <file2>\n";
		return 1;
	}

	ifstream file1(argv[1]);
	if (!file1.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}
	ifstream file2(argv[2]);
	if (!file1.is_open())
	{
		cout << "Failed to open " << argv[2] << " for reading\n";
		return 1;
	}

	string line1, line2;
	int countLine = 1;
	bool isCompare = true;

	while (!file1.eof() && !file2.eof())
	{
		getline(file1, line1);
		getline(file2, line2);
		if (line1 != line2)
		{
			isCompare = false;
			break;
		}
		countLine++;
	}
	if (isCompare)
	{
		cout << "Files are equal\n"; 
	}
	else
	{
		cout << "Files are different. Line number is " << countLine << "\n"; 
	}
   
}