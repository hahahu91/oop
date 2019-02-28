// multMatrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <array>

using namespace std;

using MatrixRow = array<double, 3>;
using Matrix3x3 = array<MatrixRow, 3>;


bool LoadMatrixFromFile(const string& fileNameMatrix, Matrix3x3& matrix)
{
	ifstream file(fileNameMatrix);
	if (!file.is_open())
	{
		return false;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			file >> matrix[i][j];
		}
	}

	return true;
}
double MulptiplyRowByColumn(const MatrixRow& row, const Matrix3x3& matrix, const size_t columnNumber)
{
	double result = 0;
	for (size_t i = 0; i < row.size(); ++i)
	{
		result += row[i] * matrix[i][columnNumber];
	}
	return result;
}
bool MultiplyMatrix(const Matrix3x3& matrix1, const Matrix3x3& matrix2, Matrix3x3& result)
{

	const size_t rowsCount = matrix1.size();
	const size_t columnsCount = matrix1[0].size();

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnsCount; j++)
		{
			result[i][j] = MulptiplyRowByColumn(matrix1[i], matrix2, j);
		}
	}


	return true;
}
void PrintMatrix3x3(const Matrix3x3& matrix)
{
	const size_t rows = matrix.size();
	const size_t columns = matrix[0].size();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << matrix[i][j];
			if (j != columns-1)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: multmatrix.exe <matrix file1> <matrix file2>\n";
		return 1;
	}
	Matrix3x3 matrix1;
	Matrix3x3 matrix2;
	Matrix3x3 result;
	
	if (!LoadMatrixFromFile(argv[1], matrix1) || !LoadMatrixFromFile(argv[2], matrix2))
	{
		cout << "Failed to open file for reading\n";
		return 1;
	}
	else
	{
		if(MultiplyMatrix(matrix1, matrix2, result)) {
			PrintMatrix3x3(result);
		}
		else
		{
			cout << "Error/n";
		}
	}

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
