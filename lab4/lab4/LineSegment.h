#pragma once
#include "CShape.h"
#include "Point.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment(CPoint const& startPont, CPoint const& endPoint, const std::string& outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	void Draw(ICanvas& canvas) override;

private: 
	CPoint startPoint;
	CPoint endPoint;
	void AppendProperties(std::ostream& strm) const;
};
