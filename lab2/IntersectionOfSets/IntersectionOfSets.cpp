// IntersectionOfSets.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "CrossSet.h"
#include "CreateSet.h"

void PrintSet(std::set<int> setNumbers)
{
	for (int number : setNumbers)
	{
		std::cout << number << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n"
			 << "Usage: IntersectionOfSets.exe <N>\n";
		return 1;
	}

	int n = atoi(argv[1]);

	setlocale(LC_ALL, "Russian");

	std::set<int> setNumbers1 = CreateSetOfNumbersFrom1To(n, &IsDividedBySumOfItsDigits);
	std::cout << "Множество чисел делящихся на сумму их чисел:\n";
	PrintSet(setNumbers1);

	std::set<int> setNumbers2 = CreateSetOfNumbersFrom1To(n, &IsSumOfDigitsIsEven);
	std::cout << "Множество чисел у которых сумма их чисел четная:\n";
	PrintSet(setNumbers2);

	std::cout << "Пересечение этих множеств:\n";
	PrintSet(CrossSet(setNumbers1, setNumbers2));

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
