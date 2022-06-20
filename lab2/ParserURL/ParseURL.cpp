#include "pch.h"
#include <regex>

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::smatch match;
	std::regex rx(R"(^(http|https|ftp)://(\w+(\.\w+)+)(:(\d{1,5}))?/?(.+)?$)", std::regex::icase); 
	bool found = std::regex_search(url, match, rx);

	if (found) 
	{
		host = match[2].str();
		document = match[6].str();

		std::string s = match[4].str();
		if (s != "")
			port = std::stoi(match[5].str());
		if (!port or port < 1 or port > 65535)
		{
			if (match[1].str() == "http")
				port = 80;
			else if (match[1].str() == "https")
				port = 443;
			else if (match[1].str() == "ftp")
				port = 21;	
		}
		return true;
	}
	else 
		return false;
}