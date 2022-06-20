#include "Parsing.h"
#include <regex>

std::pair<int, std::string> ParsingNumberAndString(std::string inputString)
{
	int channel = atoi(inputString.c_str());
	size_t channelLength = std::to_string(channel).length();
	inputString = std::regex_replace(inputString, std::regex("^ +| +$|( ) +"), "$1");
	std::string::size_type pos = inputString.find(std::to_string(channel));
	if (pos != std::string::npos)
	{
		inputString.erase(pos, channelLength);
	}

	std::string channelName = std::regex_replace(inputString, std::regex("^ +| +$|( ) +"), "$1");

	std::pair<int, std::string> channelNumberAndName;
	channelNumberAndName.first = channel;
	channelNumberAndName.second = channelName;

	return channelNumberAndName;
}