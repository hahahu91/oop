// lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "CAction.h"
#include <Windows.h>
#include "CCanvas.h"
#include "ICanvasDrawable.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "LineSegment.h"
#include "CRectangle.h"

using namespace std;
void Draw(CCanvas& canvas, const std::vector<ICanvasDrawable*>& vObjs /* Написать недостающий код */)
{
	// 1. Рисуем фон
	canvas.Background();
	
	for (auto& obj : vObjs)
	{
		obj->Draw(canvas);
	}
	/* Написать недостающий код */
}

int main()
{
	std::vector<ICanvasDrawable*> v;
	CCanvas canvas;
	auto sun = CCircle({ 750, 70 }, 70, "fec821", "ffff00");
	v.push_back(&sun);

	auto arms = CRectangle({ 240, 225 }, 160, 25, "000000", "fcd5b5");
	v.push_back(&arms);
	auto body = CTriangle({ 320, 180 }, { 250, 350 }, { 390, 350 }, "000000", "00b0f0");
	v.push_back(&body);
	auto leg1 = CRectangle({ 295, 350 }, 15, 50, "000000", "f81bd");
	v.push_back(&leg1);
	auto leg2 = CRectangle({ 335, 350 }, 15, 50, "000000", "f81bd");
	v.push_back(&leg2);
	auto head = CCircle({ 320, 165 }, 35, "000000", "fcd5b5");
	v.push_back(&head);
	auto eye1 = CCircle({ 310, 150 }, 5, "000000", "000000");
	v.push_back(&eye1);
	auto eye2 = CCircle({ 330, 150 }, 5, "000000", "000000");
	v.push_back(&eye2);

	auto bowL = CTriangle({ 320, 130 }, { 345, 115 }, { 345, 145 }, "000000", "ff0000");
	v.push_back(&bowL);
	auto bowR = CTriangle({ 320, 130 }, { 295, 115 }, { 295, 145 }, "000000", "ff0000");
	v.push_back(&bowR);

	auto ls = CLineSegment({ 400, 225 }, { 380, 140 }, "000000");
	v.push_back(&ls);
	auto ball = CCircle({ 380, 105 }, 35, "000000", "00b0f0");
	v.push_back(&ball);	
	
	auto nose = CLineSegment({ 320, 165 }, { 320, 170 }, "00b0f0");
	v.push_back(&nose);
		
	auto mouthL = CLineSegment({ 320, 180 }, { 310, 175 }, "ff0000");
	v.push_back(&mouthL);
	auto mouthR = CLineSegment({ 320, 180 }, { 330, 175 }, "ff0000");
	v.push_back(&mouthR);

	Draw(canvas, v);

	CAction action(cin, cout);
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!action.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	action.PrintShapeWithMaxArea();
	action.PrintShapeWithMinPerimeter();
	action.DrawShapes();

	return 0;
}