
#include "pch.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

void pack(ifstream& input, ofstream& output)
{
	char ch;
	int amount = 0;
	char prevCh = '\0';
	if (input.get(prevCh))
		++amount;
	while (input.get(ch))
	{
		if (prevCh != ch)
		{
			output << amount << prevCh;
			prevCh = ch;
			amount = 0;
		} 
		++amount;
	}
	if (amount != 0)
	{
		output << amount << prevCh;
	}
}


void unpack(ifstream& input, ofstream& output)
{
	//char ch = '\0';
	//input.get(amount);
	//input.get(ch);
	int amount;
	char ch;
	// —читываем в переменную ch символ из входного потока
	// возвращаем значение, приводимое к bool, которое сигнализирует об успехе
	while (input.get(char(amount)) && input.get(ch))
	{
		if (!output.put(ch))
		{
			cout << "Failed to save data on disk\n";
		}
	}
	//while (input.get(ch))
	//{

		//if (amount == ch)
	//		output.put(ch);
		//input.get(amount);
//input.get(ch);
		//for (int i = 0; i < int(amount); i++)
			//output.put(ch);

	//}
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid argument count\n"
			 << argc << "\n"
				  << "Usage: rle.exe pack <input file> <output file>\nOr: rle.exe unpack <input file> <output file>\n";
		return 1;
	}

	ifstream inputFile;
	inputFile.open(argv[2]);

	ofstream outputFile;
	outputFile.open(argv[3]);

	if (string(argv[1]) == "pack")
		pack(inputFile, outputFile);
	else if (string(argv[1]) == "unpack")
		pack(inputFile, outputFile);

	outputFile.flush();

	return 0;
}