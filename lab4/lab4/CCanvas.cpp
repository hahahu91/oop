#include "CCanvas.h"
#include <iostream>

CCanvas::CCanvas()
{
}

Color CCanvas::ToRGB(uint32_t lineColor)
{
	return Color((lineColor / (256 * 256) % 256)
		, (lineColor / 256 % 256)
		, (lineColor % 256));
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	Color color = ToRGB(lineColor);
	pen = CreatePen(PS_SOLID, 2, RGB(color.r, color.g, color.b));
	SelectObject(dc, pen);
	MoveToEx(dc, int(from.x), int(from.y), 0);
	LineTo(dc, int(to.x), int(to.y));
	DeleteObject(pen);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
	//const int S = points.size();
	POINT poly[8] = {};
	for (size_t i = 0; i < points.size();i++)
	{
		poly[i] = { (long)points[i].x, (long)points[i].y };
	}
	Color color = ToRGB(fillColor);

	brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	SelectObject(dc, brush);
	Polygon(dc, poly, points.size());
	DeleteObject(brush);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	Color color = ToRGB(lineColor);
	pen = CreatePen(PS_SOLID, 2, RGB(color.r, color.g, color.b));
	SelectObject(dc, pen);
	Ellipse(dc, int(center.x - radius), int(center.y - radius), int(center.x + radius), int(center.y + radius));
	DeleteObject(pen);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	Color color = ToRGB(fillColor);
	brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	SelectObject(dc, brush);
	Ellipse(dc, int(center.x - radius), int(center.y - radius), int(center.x + radius), int(center.y + radius));
	DeleteObject(brush);
}

void CCanvas::Background()
{
	brush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 255, 255)); // Создаём кисть определённого стиля и цвета
	//brush = CreateSolidBrush(RGB(0, 255, 0)); //Создаём кисть определённого стиля и цвета
	SelectObject(dc, brush); //Выбираем кисть
	GetWindowRect(hwnd, &window); //Узнаём координаты

	Rectangle(dc, 0, 0, window.right, window.bottom); //Нарисовали прямоугольник, закрашенный неким стилем
	DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти

	//brush = CreateSolidBrush(RGB(0, 0, 255)); //Создаём кисть определённого стиля и цвета
	//SelectObject(dc, brush); //Выбираем кисть
	//Rectangle(dc, 0, 0, window.right, 170); //Рисуем новый прямоугольник, который будет небом
	//DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти

	//brush = CreateSolidBrush(RGB(255, 255, 0)); //Создаём кисть определённого стиля и цвета
	//SelectObject(dc, brush); //Выбираем кисть
	//Ellipse(dc, window.right - 200, 20, window.right - 300, 120);
	//DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти

	//brush = CreateSolidBrush(RGB(30, 46, 234)); //Создаём кисть определённого стиля и цвета
	//SelectObject(dc, brush); //Выбираем кисть
	//Ellipse(dc, 399, 312, 400 + 399, 312 + 140); //Озеро.
	//DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти
}
CCanvas::~CCanvas()
{
	ReleaseDC(hwnd, dc);
}