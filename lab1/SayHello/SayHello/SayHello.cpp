// SayHello.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "What is your name?\n";

	string name;

	getline(cin, name);
	if (name.empty())
	{
		name = "anonimus :)";
	}

	cout << "Hello " << name;
}
