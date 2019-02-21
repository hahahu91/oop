// calcbits.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

int BitCount(unsigned int x)
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

	int byte = 0;	
	try
	{
		byte = stoi(argv[1]);
		if (byte <= UINT8_MAX && byte >= 0)
		{
			cout << BitCount(byte) << endl;
		}
		else
		{
			cout << "Invalid argument\n";
			return 1;
		} 
	}
	catch (const std::invalid_argument& err)
	{
		cout << err.what();	
		return 1;
	}
	return 0;
}
