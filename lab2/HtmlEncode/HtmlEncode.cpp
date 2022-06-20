#include "pch.h"

std::string Encode(const char ch) {
	switch (ch)
	{
	case '\'':
		return "&apos;";
	case '\"':
		return "&quot;";
	case '<':
		return "&lt;";
	case '>':
		return "&gt;";
	case '&':
		return "&amp;";
	default:
		return std::string(1, ch);
	}
}

std::string HtmlEncode(const std::string& text)
{
	std::string encode = "";
	for (char ch : text)
	{
		encode += Encode(ch);	
	}

	return encode;
}
