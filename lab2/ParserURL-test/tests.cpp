#include "pch.h"
#include "ParserURL/ParseURL.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "../catch2/catch.hpp"
// using namespace std;


TEST_CASE("ParseURL() Defines the correctness of the URL, as well as allocates information from it.")
{
	Protocol protocol;
	int port = 0;
	std::string host, document;
	std::string url = R"(http://www.mysite.com/docs/document1.html?page=30&lang=en#title)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(port == 80);
	CHECK(host == "www.mysite.com");
	CHECK(document == "docs/document1.html?page=30&lang=en#title");
}
TEST_CASE("ParseURL() Defines the correctness of the URL doc is null and https port default, as well as allocates information from it.")
{
	Protocol protocol;
	int port = 0;
	std::string host, document;
	std::string url = R"(https://mysite.com)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(port == 443);
	CHECK(host == "mysite.com");
	CHECK(document == "");
}




TEST_CASE("ParseURL() with a port but without a document")
{
	Protocol protocol;
	int port = 0;
	std::string host, document;
	std::string url = R"(http://mysite.com:65535)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(port == 65535);
	CHECK(host == "mysite.com");
	CHECK(document == "");
}

TEST_CASE("ParseURL() port is too big")
{
	Protocol protocol;
	int port = 0;
	std::string host, document;
	std::string url = R"(ftp://65535.com:65536/document1.html)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(port == 21);
	CHECK(host == "65535.com");
	CHECK(document == "document1.html");
}

TEST_CASE("ParseURL() 2 dot in a row in the host")
{
	Protocol protocol;
	int port = 0;
	std::string host, document;
	std::string url = R"(ftp://mysite..com:62532/document1.html)";
	CHECK(ParseURL(url, protocol, port, host, document) == false);
}
