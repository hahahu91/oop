// compare.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;
bool Compare(const string& inFile1Name, const string& inFile2Name)
{
	ifstream file1(inFile1Name);
	ifstream file2(inFile2Name);
	if (!file1.is_open() || !file2.is_open())
	{
		cout << "Failed to open file for reading\n";
		return false;
	}

	string line1, line2;
	int countLine = 1;
	bool contentIsEqual = true;

	while (!file1.eof() && !file2.eof())
	{
		getline(file1, line1);
		getline(file2, line2);
		if (line1 != line2)
		{
			contentIsEqual = false;
			break;
		}
		countLine++;
	}
	if (!file1.eof() || !file2.eof())
	{
		contentIsEqual = false;
	}
	if (contentIsEqual)
	{
		cout << "Files are equal\n";
	}
	else
	{
		cout << "Files are different. Line number is " << countLine << "\n";
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: compare.exe <file1> <file2>\n";
		return 1;
	}

	if (Compare(argv[1], argv[2]))
	{
		return 0;
	}
	else
	{
		return 1;
	}  
}