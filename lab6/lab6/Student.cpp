#include "pch.h"
#include "CStudent.h"
#include <iostream>
#include <stdexcept>
#include <string>

int main()
{
	size_t age;
	std::string name, surname, patronymic;

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!(std::cin >> name >> surname >> patronymic >> age))
		{
			std::cout << "Unknown command!" << std::endl;
		}
		else
		{
			try
			{
				CStudent st(name, surname, patronymic, age);
				std::cout << "area: " << "t.GetArea()" << "\n"
						  << "perimeter: " << "t.GetPerimeter()" << "\n";
			}
			catch (const std::invalid_argument e)
			{
				std::cout << e.what();
			}
			catch (const std::domain_error e)
			{
				std::cout << e.what();
			}
		}
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
