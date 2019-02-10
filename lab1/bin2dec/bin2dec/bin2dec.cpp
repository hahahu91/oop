// bin2dec.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: bin2dec.exe <binary number>\n";
		return 1;
	}

	string str = argv[1];
	double decNumber = 0;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] > '1' || str[i] < '0')
		{
			cout << "Invalid argument\n"
				 << "Usage: bin2dec.exe <binary number>\n";
			return 1;
		}
		if (str[i] == '1')
		{
			decNumber += pow(2, str.length() - i - 1);
		}
	}
	cout << decNumber << endl;
	return 0;	
}

