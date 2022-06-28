#pragma once
#include "CSolidShape.h"
#include "Point.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle(CPoint const& leftTopAngle, double const& width, double const& height, const std::string& outlineColor, const std::string& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

	void Draw(ICanvas& canvas) override;

private:
	CPoint leftTopAngle;
	double width, height;
	void AppendSolidProperties(std::ostream& strm) const;
};