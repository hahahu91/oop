#pragma once
#include "pch.h"

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);