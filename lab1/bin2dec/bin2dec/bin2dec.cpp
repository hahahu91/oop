// bin2dec.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

bool BinToNumber(const string& decInStr, long& number)
{
	string str = decInStr;
	number = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[0] > '1' || str[0] < '0')
		{
			return false;
		}
		number = number * 2 + (str[i] - '0');
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: bin2dec.exe <binary number>\n";
		return 1;
	}

	long number;
	if (BinToNumber(argv[1], number))
	{
		cout << number << endl;
	}
	else
	{
		cout << "Invalid argument\n"
			 << "Usage: bin2dec.exe <binary number>\n";
		return 1;
	}
	return 0;	
}

