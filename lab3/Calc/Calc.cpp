// TvSet.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Calculate.h"
#include "Menu.h"
#include <iostream>

using namespace std;

int main()
{
	Calculate calc;
	Menu remoteControl(calc, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}
