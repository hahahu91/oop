#include <Windows.h>
#include <iostream>

class TreePicture
{
	void line(const HDC& dc, const int x1, const int y1, const int x2, const int y2)
	{
		MoveToEx(dc, x1, y1, 0);
		LineTo(dc, x2, y2);
	}

public:
	void show(const HWND& hwnd, const HDC& dc, const int X, const int Y);
};

class House
{
public:
	void show(const HWND& hwnd, const HDC& dc, const int X, const int Y);
};

void House::show(const HWND& hwnd, const HDC& dc, const int X, const int Y)
{
	/*ФАСАД ДОМА*/
	HBRUSH brush = CreateSolidBrush(RGB(254, 255, 220));
	SelectObject(dc, brush);
	Rectangle(dc, X, Y + 260, X + 130, Y + 400);
	DeleteObject(brush);

	/*ТРЕУГОЛЬНАЯ КРЫША*/
	POINT poly[3] = { { X, Y + 260 }, { X + 130, Y + 260 }, { X + 130 / 2, Y + 200 } };
	brush = CreateHatchBrush(HS_DIAGCROSS, RGB(199, 214, 255));
	SelectObject(dc, brush);
	Polygon(dc, poly, 3);
	DeleteObject(brush);

	/*БОК КРЫШИ ПАРАЛЛЕЛОГРАММ*/
	POINT poly2[4] = { { X + 65, Y + 200 }, { X + 280, Y + 200 }, { X + 345, Y + 260 }, { X + 130, Y + 260 } };
	brush = CreateHatchBrush(HS_HORIZONTAL, RGB(0, 0, 255));
	SelectObject(dc, brush);
	Polygon(dc, poly2, 4);
	DeleteObject(brush);

	/*БОК ДОМА*/
	brush = CreateHatchBrush(7, RGB(200, 255, 200));
	SelectObject(dc, brush);
	Rectangle(dc, X + 345, Y + 260, X + 130, Y + 400);
	DeleteObject(brush);

	/*ДВЕРЬ*/
	brush = CreateSolidBrush(RGB(175, 75, 0));
	SelectObject(dc, brush);
	Rectangle(dc, X + 70, Y + 320, X + 110, Y + 400);
	DeleteObject(brush);

	/*ОКНА*/
	brush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 255, 0));
	SelectObject(dc, brush);
	Rectangle(dc, X + 150, Y + 300, X + 190, Y + 340);
	Rectangle(dc, X + 220, Y + 300, X + 260, Y + 340);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(200, 200, 200));
	SelectObject(dc, brush);
	Rectangle(dc, X + 290, Y + 300, X + 330, Y + 340);
	DeleteObject(brush);
}

void TreePicture::show(const HWND& hwnd, const HDC& dc, const int X, const int Y)
{
	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	SelectObject(dc, brush);
	line(dc, X, Y, X, Y - 150); //Здесь 150 - это высота ствола, рисование идёт снизу к верху.

	/*Рисуем ветки*/
	line(dc, X, Y - 75, X - 50, Y - 75 - 15);
	// circle == (X,Y, X+R, Y+R)
	Ellipse(dc, X - 70, Y - 105, X - 40, Y - 105 + 30); //Подгоняем листья

	line(dc, X, Y - 95, X - 50, Y - 95 - 15);
	Ellipse(dc, X - 75, Y - 120, X - 50, Y - 120 + 15); //Подгоняем листья
	Ellipse(dc, X - 50, Y - 130, X - 35, Y - 120 + 15); //Подгоняем листья

	Ellipse(dc, X - 10, Y - 150, X + 10, Y - 150 + 15); //Подгоняем листья

	line(dc, X, Y - 60, X + 80, Y - 165); //Ветви
	line(dc, X, Y - 90, X + 30, Y - 135);
	line(dc, X + 25, Y - 95, X + 85, Y - 100);
	line(dc, X + 50, Y - 130, X + 55, Y - 170);

	Ellipse(dc, 15 + X + 55, 15 + Y - 170, 15 + X + 75, 15 + Y - 190); //листва
	Ellipse(dc, 15 + X + 34, 15 + Y - 180, 15 + X + 46, 15 + Y - 200);
	Ellipse(dc, 25 + X + (-5), 25 + Y - 120, 25 + X + 7, 25 + Y - 144);
	Ellipse(dc, 15 + X + 55, 15 + Y - 103, 15 + X + 75, 15 + Y - 127);
	Ellipse(dc, 15 + X + 10, 15 + Y - 140, 15 + X + 28, 15 + Y - 158);

	DeleteObject(brush);
};

int main()
{
	HWND hwnd = GetConsoleWindow(); //Берём ориентир на консольное окно (В нём будем рисовать)
	HDC dc = GetDC(hwnd); //Цепляемся к консольному окну
	RECT window = {}; //Переменная window будет использована для получения ширины и высоты окна
	HBRUSH brush; //Переменная brush - это кисть, она будет использоваться для закрашивания

	// 1. Рисуем фон

	brush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 255, 0)); // Создаём кисть определённого стиля и цвета
	SelectObject(dc, brush); //Выбираем кисть
	RECT WinCoord = {}; //Массив координат окна
	GetWindowRect(hwnd, &WinCoord); //Узнаём координаты

	Rectangle(dc, 0, 0, WinCoord.right, WinCoord.bottom); //Нарисовали прямоугольник, закрашенный неким стилем
	DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти

	brush = CreateSolidBrush(RGB(0, 0, 255)); //Создаём кисть определённого стиля и цвета
	SelectObject(dc, brush); //Выбираем кисть
	Rectangle(dc, 0, 0, WinCoord.right, 170); //Рисуем новый прямоугольник, который будет небом
	DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти

	brush = CreateSolidBrush(RGB(255, 255, 0)); //Создаём кисть определённого стиля и цвета
	SelectObject(dc, brush); //Выбираем кисть
	Ellipse(dc, WinCoord.right - 200, 20, WinCoord.right - 300, 120);
	DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти

	brush = CreateSolidBrush(RGB(30, 46, 234)); //Создаём кисть определённого стиля и цвета
	SelectObject(dc, brush); //Выбираем кисть
	Ellipse(dc, 399, 312, 400 + 399, 312 + 140); //Озеро.
	DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти

	/*РИСУЕМ ДЕРЕВО*/
	TreePicture Tree;
	Tree.show(hwnd, dc, 80, 440);
	/**/

	/*РИСУЕМ ДОМ*/
	House house;
	house.show(hwnd, dc, 410, -90);
	house.show(hwnd, dc, 10, 70);
	house.show(hwnd, dc, 150, 90);

	Tree.show(hwnd, dc, 400, 190);
	Tree.show(hwnd, dc, 370, 198);
	Tree.show(hwnd, dc, 270, 256);
	Tree.show(hwnd, dc, 70, 247);

	ReleaseDC(hwnd, dc); //Освобождаем общий или оконный (не влияющий на класс или локальность) контекст устpойства, делая его доступным для дpугих пpикладных задач.

	std::cin.get();
}