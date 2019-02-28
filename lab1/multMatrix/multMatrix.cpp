// multMatrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <array>
#include <fstream>
#include <iostream>

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
			if (!(file >> matrix[i][j]))
			{
				return false;
			}
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

void PrintMatrix(const Matrix3x3& matrix)
{
	const size_t rows = matrix.size();
	const size_t columns = matrix[0].size();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << matrix[i][j];
			if (j != columns - 1)
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

	if (!LoadMatrixFromFile(argv[1], matrix1) || !LoadMatrixFromFile(argv[2], matrix2))
	{
		cout << "Failed to open file for reading\n";
		return 1;
	}
	else
	{
		Matrix3x3 result;
		if (MultiplyMatrix(matrix1, matrix2, result))
		{
			PrintMatrix(result);
		}
		else
		{
			cout << "Error/n";
		}
	}

	return 0;
}
