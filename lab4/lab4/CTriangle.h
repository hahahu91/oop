#pragma once
#include "Point.h"
#include "CSolidShape.h"

class CTriangle final :public CSolidShape
{
public:
	CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, std::string& outlineColor, std::string& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint vertex1, vertex2, vertex3;
	void AppendSolidProperties(std::ostream& strm) const;
};
