#pragma once
#include "pch.h"
#include "IShape.h"
#include "CAction.h"
#include "CCircle.h"
#include "LineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Point.h"

using namespace std;

class IShape;

CAction::CAction(std::istream& input, std::ostream& output)
	: input(input)
	, output(output)
	, actionMap({
		{ "Circle", bind(&CAction::AddCircle, this, placeholders::_1) },
		{ "Rectangle", bind(&CAction::AddRectangle, this, placeholders::_1) },
		{ "LineSegment", bind(&CAction::AddLineSegment, this, placeholders::_1) },
		{ "Triangle", bind(&CAction::AddTriangle, this, placeholders::_1) }	
	})
{
}
bool CAction::HandleCommand()
{
	string commandLine;
	getline(input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = actionMap.find(action);
	if (it != actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

void CAction::Info()
{
	for (const auto& shape : shapeList)
	{
		output << shape->ToString() << endl;
	}
}

void CAction::PrintShapeWithMinPerimeter()
{
	if (shapeList.size() != 0)
	{
		auto minPerimeterShape = std::min_element(shapeList.begin(), shapeList.end(), [](const auto& first, const auto& second)
		{
			return first->GetPerimeter() < second->GetPerimeter();
		});
		output << "Min perimeter shape:\n" << (*minPerimeterShape)->ToString();
	}
}

void CAction::PrintShapeWithMaxArea()
{
	if (shapeList.size() != 0)
	{
		auto maxAreaShape = std::min_element(shapeList.begin(), shapeList.end(), [](const auto& first, const auto& second) {
			return first->GetArea() > second->GetArea();
		});
		output << "Max area shape:\n" << (*maxAreaShape)->ToString();
	}
}

bool CAction::AddCircle(std::istream& args)
{
	vector<string> words;
	std::string tmp;
	while (args >> tmp)
		words.push_back(tmp);
	if (words.size() < 3 || words.size() > 5)
	{
		throw invalid_argument("Incorrect count of arguments!\nUsage: Circle center.x center.y radius [outline color, fill color]\n");
	}
	else
	{
		CPoint center{ stod(words[0]), stod(words[1]) };
		double radius = stod(words[2]);
		string outlineColor = "000000";
		string fillColor = "FFFFFF";
		if (words.size() > 3)
		{
			outlineColor = words[3];
			if (words.size() == 5)
				fillColor = words[4];
		}		

		auto circle = make_unique<CCircle>(center, radius, outlineColor, fillColor);
		shapeList.push_back(std::move(circle));
	}
	return true;
}
bool CAction::AddRectangle(std::istream& args)
{
	vector<string> words;
	std::string tmp;
	while (args >> tmp)
		words.push_back(tmp);
	if (words.size() < 4 || words.size() > 6)
	{
		throw invalid_argument("Incorrect count of arguments!\nUsage: Rectangle leftTopAngle.x leftTopAngle.y widht height [outline color, fill color]\n");
	}
	else
	{
		CPoint leftTopAngle{ stod(words[0]), stod(words[1]) };
		double widht = stod(words[2]);
		double height = stod(words[3]);
		string outlineColor = "000000";
		string fillColor = "FFFFFF";
		if (words.size() > 4)
		{
			outlineColor = words[4];
			if (words.size() == 6)
				fillColor = words[5];
		}

		auto rectangle = make_unique<CRectangle>(leftTopAngle, widht, height, outlineColor, fillColor);
		shapeList.push_back(std::move(rectangle));
	}
	return true;
}
bool CAction::AddTriangle(std::istream& args)
{
	vector<string> words;
	std::string tmp;
	while (args >> tmp)
		words.push_back(tmp);
	if (words.size() < 6 || words.size() > 8)
	{
		throw invalid_argument("Incorrect count of arguments!\nUsage: Triangle vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y [outline color, fill color]\n");
	}
	else
	{
		CPoint vertex1{ stod(words[0]), stod(words[1]) };
		CPoint vertex2{ stod(words[2]), stod(words[3]) };
		CPoint vertex3{ stod(words[4]), stod(words[5]) };
		string outlineColor = "000000";
		string fillColor = "FFFFFF";
		if (words.size() > 6)
		{
			outlineColor = words[6];
			if (words.size() == 8)
				fillColor = words[7];
		}

		auto triangle = make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
		shapeList.push_back(std::move(triangle));
	}
	return true;
}
bool CAction::AddLineSegment(std::istream& args)
{
	vector<string> words;
	std::string tmp;
	while (args >> tmp)
		words.push_back(tmp);
	if (words.size() < 4 || words.size() > 6)
	{
		throw invalid_argument("Incorrect count of arguments!\nUsage: LineSegment start.x start.y end.x end.y [outline color, fill color]\n");
	}
	else
	{
		CPoint start{ stod(words[0]), stod(words[1]) };
		CPoint end{ stod(words[2]), stod(words[3]) };
		string outlineColor = "000000";
		string fillColor = "FFFFFF";
		if (words.size() > 4)
		{
			outlineColor = words[4];
			if (words.size() == 6)
				fillColor = words[5];
		}

		auto lineSegment = make_unique<CLineSegment>(start, end, outlineColor);
		shapeList.push_back(std::move(lineSegment));
	}
	return true;
}

void CAction::DrawShapes() const
{
	output << "Drawing Shapes:\n";
}