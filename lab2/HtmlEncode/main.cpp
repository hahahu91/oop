#include "pch.h"
#include <fstream>
#include <iostream>
#include "HtmlEncode.h"

using namespace std;


bool ReadFileToString(const std::string& fileName, std::string& str)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Failed to open file for reading\n";
		return false;
	}
	str = "";
	std::string line;

	while (!file.eof())
	{
		getline(file, line);
		str += line;
	}

	if (!file.eof())
	{
		cout << "Reading error\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: htmlencode.exe\n";
		return 1;
	}
	string str;

	while (std::getline(std::cin, str))
	{
		cout << HtmlEncode(str) << endl;
	}

	return 1;
}
