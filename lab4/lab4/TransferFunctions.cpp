#include "pch.h"
#include "TransferFunctions.h"

uint32_t ToUINT32FromString(std::string& outlineColor)
{
	std::istringstream reader(outlineColor);
	uint32_t color = 0;

	reader >> std::hex >> color;

	return color;
}