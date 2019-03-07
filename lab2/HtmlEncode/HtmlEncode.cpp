#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string HtmlEncode(const string& text)
{
	char ch;
	string Encode = "";
	for (size_t i = 0; i < text.size(); i++)
	{
		ch = text[i];
		switch (ch)
		{
			case 0x27:
				Encode += "&apos;";
				break;
			case 0x22:
				Encode += "&quot;";
				break;
			case '<':
				Encode += "&lt;";
				break;
			case '>':
				Encode += "&gt;";
				break;
			case '&':
				Encode += "&amp;";
				break;
			default:
				Encode += ch;
		}
	}
	return Encode;
}
bool ReadFileToString(const string& fileName, string& str)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Failed to open file for reading\n";
		return false;
	}
	str = "";
	string line;

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
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: htmlencode.exe <FileName>\n";
		return 1;
	}
	string str;
	if (ReadFileToString(argv[1], str))
	{
		string Encode = HtmlEncode(str);
		cout << Encode << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}
