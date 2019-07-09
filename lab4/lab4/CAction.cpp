#pragma once
#include "pch.h"
#include "IShape.h"
#include "CAction.h"
#include "CCircle.h"
#include "LineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <vector>
#include "Point.h"

using namespace std;

class IShape;

CAction::CAction(std::istream& input, std::ostream& output)
	: input(input)
	, output(output)
	, actionMap({
		{ "Circle", bind(&CAction::AddCircle, this, placeholders::_1) },
		{ "Rectangle", bind(&CAction::AddCircle, this, placeholders::_1) },
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
		cout << shape->ToString() << endl;
	}
}

void CAction::PrintShapeWithMinPerimeter()
{}

void CAction::PrintShapeWithMaxArea()
{}

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
	return false;
}
bool CAction::AddTriangle(std::istream& args)
{
	return false;
}
bool CAction::AddLineSegment(std::istream& args)
{
	return false;
}

