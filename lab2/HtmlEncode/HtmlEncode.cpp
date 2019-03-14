#include "pch.h"

std::string Encode(const char ch) {
	switch (ch)
	{
	case 0x27:
		return "&apos;";
	case 0x22:
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
	char ch;
	std::string encode = "";
	for (size_t i = 0; i < text.size(); i++)
	{
		ch = text[i];
		encode += Encode(ch);	
	}
	return encode;
}
