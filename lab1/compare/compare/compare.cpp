// compare.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool Compare(char& FileName1, char& FileName2)
{
	ifstream file1(&FileName1);
	ifstream file2(&FileName2);
	if (!file1.is_open() || !file2.is_open())
	{
		cout << "Failed to open file for reading\n";
		return false;
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

	if (Compare(*argv[1], *argv[2]))
	{
		return 0;
	}
	else
	{
		return 1;
	}  
}