// bin2dec.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

long BinInStr2dec(const string& decInStr)
{
	string str = decInStr;
	long decNumber = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		string bite = str.substr(i, 1);
		if (bite[0] > '1' || bite[0] < '0')
		{
			return -1;
		}
		decNumber = decNumber * 2 + (stoi(bite));
	}
	return decNumber;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: bin2dec.exe <binary number>\n";
		return 1;
	}

	string str = argv[1];
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] > '1' || str[i] < '0')
		{
			cout << "Invalid argument\n"
				 << "Usage: bin2dec.exe <binary number>\n";
			return 1;
		}
	}
	cout << BinInStr2dec(str) << endl;
	return 0;	
}

