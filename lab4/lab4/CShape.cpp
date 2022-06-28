#include "pch.h"
#include "CShape.h"
#include "TransferFunctions.h"

CShape::CShape(const std::string& type, const std::string& outlineColor)
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
		 << std::fixed << std::setprecision(2)
		 << "\tArea = "  << GetArea() << std::endl
		 << "\tPerimeter = " << GetPerimeter() << std::endl
		 << "\tOutline color = " << std::setfill('0') << std::setw(6) << std::hex << GetOutLineColor() << std::endl;
	AppendProperties(strm);
	return strm.str();
}