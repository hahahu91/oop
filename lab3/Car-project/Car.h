#pragma once

enum class Direction
{
	Forward,
	Back,
	Stand
};


class Car
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(size_t speed);
	int GetGear() const;
	bool IsOnEngine() const;
	Direction GetDirection() const;
	size_t GetSpeed() const;


private:
	bool CheckPossibilitySwitchGear(int gear, size_t speed, Direction dir) const;
	bool CheckSpeedForThisGear(int gear, size_t speed) const;
	int m_gear = 0;
	size_t m_speed = 0;
	bool m_isOnEngine = false;
	Direction m_direction = Direction::Stand;
};
