#pragma once
#include <boost/noncopyable.hpp>
#include "IShape.h"

class IShape;

// ������������ �� boost::noncopyable - ����� ������ ��������� ����������� � ������������ ����������� ������
class CAction : boost::noncopyable
{
public:
	CAction(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintShapeWithMinPerimeter();
	void PrintShapeWithMaxArea();
	void Info();

	// ����������� �� �������������� ����������� � ���, ��� �� �� ������ ������������� �������� ������������
	// CRemoteControl& operator=(const CRemoteControl &) = delete;
private:
	bool AddCircle(std::istream& args);
	bool AddRectangle(std::istream& args);
	bool AddTriangle(std::istream& args);
	bool AddLineSegment(std::istream& args);

private:
	using ActionMap = std::map<std::string, std::function<bool(std::istream& args)>>;

	std::vector<std::unique_ptr<IShape>> shapeList;
	std::istream& input;
	std::ostream& output;
	const ActionMap actionMap;
};
