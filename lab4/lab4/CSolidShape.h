#pragma once
#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape : public ISolidShape,
	public CShape					
{
public:
	CSolidShape(std::string const& type, std::string& outlineColor, std::string& fillColor);
	uint32_t GetFillColor() const override;
	uint32_t GetOutLineColor() const;
	std::string ToString() const;

private:
	uint32_t fillColor;
	void AppendProperties(std::ostream& strm) const final;
	virtual void AppendSolidProperties(std::ostream& strm) const = 0;
};
