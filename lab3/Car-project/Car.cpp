#include "pch.h"
#include "Car.h"

bool Car::TurnOnEngine()
{
	if (!IsOnEngine())
	{
		m_isOnEngine = true;
		return true;
	} 
	else 
		return false;
}

bool Car::TurnOffEngine()
{
	if (IsOnEngine())
	{
		if (m_speed != 0 && m_gear != 0)
			return false;
		m_isOnEngine = false;
		return true;
	}
	else
		return false;
}

struct Speed
{
	int min;
	int max;

	public:
	Speed(int min, int max)
			: min(min)
			, max(max)
	{}
	Speed()
		: min(0)
		, max(0)
	{
	}
};

bool Car::CheckSpeedForThisGear(int gear, size_t speed) const
{
	std::map<int, Speed> mapSpeed = { 
		{ 1, Speed(0, 20) }, 
		{ 2, Speed(20, 50) },
		{3, Speed(30, 60)},
		{4, Speed(40, 90)},
		{5, Speed(50, 150)},
		{0, Speed(0, 150)},
		{-1, Speed(0, 20)}
	};
	auto it = mapSpeed.find(gear);
	if (it == mapSpeed.end())
	{
		return false;	
	}
	return speed >= mapSpeed[gear].min && speed <= mapSpeed[gear].max;
	/*
	switch (gear)
	{
		case 1:	
			return speed >= 0 && speed <= 20;
		case 2:	
			return speed >= 20 && speed <= 50;
		case 3: 
			return speed >= 30 && speed <= 60;
		case 4: 
			return speed >= 40 && speed <= 90;
		case 5:	
			return speed >= 50 && speed <= 150;
		case -1: 
			return speed >= 0 && speed <= 20;
		case 0:	
			return speed >= 0 && speed <= 150;
		default:
			return false;
	}
	*/ 
}

bool Car::CheckPossibilitySwitchGear(int gear, size_t speed, Direction dir) const
{
	if (gear == -1 && dir == Direction::Forward)
		return false;
	if (gear >= 1 && gear <= 5 && dir == Direction::Back)
		return false;
	if (gear == -1 && dir == Direction::Back && m_gear == 0)
		return false;
	return CheckSpeedForThisGear(gear, speed);
}

bool Car::SetGear(int gear)
{
	if (!m_isOnEngine && gear != 0)
		return false;
	if (CheckPossibilitySwitchGear(gear, m_speed, m_direction))
	{
		m_gear = gear;
		return true;
	}
	else
		return false;
}

bool Car::SetSpeed(size_t speed)
{
	if (m_gear == 0 && speed > m_speed)
	{
		return false;
	}
	if (CheckSpeedForThisGear(m_gear, speed))
	{
	
		if (speed == 0)
			m_direction = Direction::Stand;
		else if (m_gear == 1)
		{
			m_direction = Direction::Forward;
		}
		else if (m_gear == -1)
		{
			m_direction = Direction::Back;
		}
		m_speed = speed;
		return true;
	}
	else
		return false;
}

int Car::GetGear() const
{
	return m_gear;
}

bool Car::IsOnEngine() const
{
	return m_isOnEngine;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

size_t Car::GetSpeed() const
{
	return m_speed;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
