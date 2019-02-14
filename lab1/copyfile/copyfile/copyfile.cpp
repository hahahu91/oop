
#include "pch.h"
#include <fstream>
#include <iostream>

using namespace std;

bool CopyFile(const string& inFileName, const string& outFileName)
{
	ifstream input(inFileName);
	if (!input.is_open())
	{
		cout << "Failed to open inputFile for reading\n";
		return false;
	}

	ofstream output(outFileName);
	if (!output.is_open())
	{
		cout << "Failed to open outFile for writing\n";
		return false;
	}

	char ch;
	while (input.get(ch))
	{
		output.put(ch);
		if (!output.put(ch))
		{
			cout << "Failed to save data on disk\n";
			return false;
		}
	}
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: copyfile.exe <input file> <output file>\n";
		return 1;
	}
	
	if (CopyFile(argv[1], argv[2]))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
