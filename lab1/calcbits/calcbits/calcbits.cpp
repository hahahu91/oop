// calcbits.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

using namespace std;

int bitcount(unsigned int x)
{
	int b;
	for (b = 0; x != 0; x >>= 1)
	{
		if (x & 0x01)
		{
			++b;
		}
	}
	return b;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: calcbits.exe <byte>\n";
		return 1;
	}

	int byte = atoi(argv[1]);
	if (byte > 0)
	{
		cout << bitcount(byte) << endl;
	}
	else
	{
		cout << "Invalid argument\n"
			 << "Usage: calcbits.exe <positive number>\n";
	}
}
