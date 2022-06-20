// lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "CAction.h"

using namespace std;

int main()
{
	CAction action(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!action.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	catch (...)
	{

	}
	action.PrintShapeWithMaxArea();
	action.PrintShapeWithMinPerimeter();

	return 0;
}