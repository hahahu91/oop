#include <string>
#include <regex>

std::string reduce(const std::string& str)
{
	return std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
}