#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape(const std::string& type, const std::string& outlineColor);
	uint32_t GetOutLineColor() const override;
	std::string ToString() const override;

private:
	uint32_t outlineColor;
	std::string type;
	virtual void AppendProperties(std::ostream& strm) const = 0;
};
