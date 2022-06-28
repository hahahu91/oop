#pragma once
#include "pch.h"
#include "CSolidShape.h"
#include "CShape.h"
#include "TransferFunctions.h"

using namespace std;

CSolidShape::CSolidShape(std::string const& type, const std::string& outlineColor, const std::string& fillColor)
	: CShape(type, outlineColor)
	, fillColor(ToUINT32FromString(fillColor))
{
}

uint32_t CSolidShape::GetOutLineColor() const
{
	return CShape::GetOutLineColor();
}

std::string CSolidShape::ToString() const
{
	return CShape::ToString();
}

uint32_t CSolidShape::GetFillColor() const
{
	return fillColor;
};

void CSolidShape::AppendProperties(std::ostream& strm) const
{
	strm << "\tFill color = " << setfill('0') << setw(6) << hex << CSolidShape::GetFillColor() << endl;
	AppendSolidProperties(strm);	
};
