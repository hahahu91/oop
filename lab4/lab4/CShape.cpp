#include "pch.h"
#include "CShape.h"

uint32_t ToUINT32FromString(std::string& outlineColor)
{
	std::istringstream reader(outlineColor);
	uint32_t color = 0;

	reader >> std::hex >> color;

	return color;
}

CShape::CShape(std::string const& type, std::string& outlineColor)
	: type(type)
	, outlineColor(ToUINT32FromString(outlineColor))
{
}

uint32_t CShape::GetOutLineColor() const
{
	return outlineColor;
}

std::string CShape::ToString() const
{
	std::ostringstream strm;
	strm << type << ":" << std::endl
		 << std::setprecision(10)
		 << "\tArea = " << GetArea() << std::endl
		 << "\tPerimeter = " << GetPerimeter() << std::endl
		 << "\tOutLineColor = " << GetOutLineColor() << std::endl;
	AppendProperties(strm);
	return strm.str();
}