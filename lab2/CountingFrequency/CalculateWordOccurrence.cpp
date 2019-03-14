#include "pch.h"
#include "UpdateWordFrequency.h"

std::map<std::string, int> CalculateWordOccurrence(std::istream& input)
{
	std::map<std::string, int> mapWords;
	std::string word;

	while (input >> word)
	{
		UpdateWordFrequency(word, mapWords);
	}

	return mapWords;
}