#pragma once
#include "CSolidShape.h"
#include "Point.h"

class CCircle final : public CSolidShape
{
public:
	CCircle(CPoint const& center, double const& radius, const std::string& outlineColor, const std::string& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

	
	void Draw(ICanvas& canvas) override;

private:
	CPoint center;
	double radius;
	void AppendSolidProperties(std::ostream& strm) const;
};