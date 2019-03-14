#include "pch.h"

void CountingFrequencyOfWord(const std::string& word, std::map<std::string, int>& map)
{
	std::string str = word;
	transform(word.begin(), word.end(), str.begin(), ::tolower);
	if (map.find(str) == map.end())
	{
		map[str] = 1;
	}
	else
	{
		map[str]++;
	}
}
std::map<std::string, int> CountFrequency()