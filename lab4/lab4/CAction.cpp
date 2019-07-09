#pragma once
#include "pch.h"
#include "IShape.h"
#include "CAction.h"
#include "CCircle.h"
#include "LineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"

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

void CAction::PrintShapeWithMinPerimeter()
{}

void CAction::PrintShapeWithMaxArea()
{}

bool CAction::AddCircle(std::istream& args)
{
	return false;
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

