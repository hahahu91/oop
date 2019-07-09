#pragma once
#include "CSolidShape.h"
#include "Point.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle(CPoint const& leftTopAngle, double const& width, double const& height, std::string& outlineColor, std::string& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint leftTopAngle;
	double width, height;
	void AppendSolidProperties(std::ostream& strm) const;
};