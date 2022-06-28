#pragma once
#include "ICanvas.h"
#include <Windows.h>
struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class CCanvas : public ICanvas
{
public:
	CCanvas();
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
	void Background();
	~CCanvas(); 

private:

	Color ToRGB(uint32_t lineColor);
	HWND hwnd = GetConsoleWindow(); //Берём ориентир на консольное окно (В нём будем рисовать)
	HDC dc = GetDC(hwnd); //Цепляемся к консольному окну
	RECT window = {}; //Переменная window будет использована для получения ширины и высоты окна
	HBRUSH brush; //Переменная brush - это кисть, она будет использоваться для закрашивания
	HPEN pen; //Переменная brush - это кисть, она будет использоваться для закрашивания
};