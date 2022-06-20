#include "pch.h"
#include "RemoteControlCar.h"

RemoteControl::RemoteControl(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "EngineOn", bind(&RemoteControl::EngineOn, this, std::placeholders::_1) },
		  { "EngineOff", bind(&RemoteControl::EngineOff, this, std::placeholders::_1) },
		  { "Info", bind(&RemoteControl::Info, this, std::placeholders::_1) },
		  { "SetGear", bind(&RemoteControl::SetGear, this, std::placeholders::_1) },
		  { "SetSpeed", bind(&RemoteControl::SetSpeed, this, std::placeholders::_1) } })
{
}

bool RemoteControl::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool RemoteControl::EngineOn(std::istream& args)
{
	m_car.TurnOnEngine();
	m_output << "Car engine is on" << std::endl;
	return true;
}
bool RemoteControl::EngineOff(std::istream& args)
{
	m_car.TurnOffEngine();
	m_output << "Car engine is off" << std::endl;
	return true;
}
bool RemoteControl::Info(std::istream& args) 
{ 
	std::string info = (m_car.IsOnEngine())
		? ("Car engine is on\nGear is: " + std::to_string(m_car.GetGear()) + "\nSpeed is: " + std::to_string(m_car.GetSpeed()) + "\n")
		: "Car engine is off\n";

	m_output << info;

	return true;
}
bool RemoteControl::SetGear(std::istream& args) { 
	int gear;
	args >> gear;
	if (m_car.SetGear(gear))
	{
		m_output << "Car set gear to " << gear << std::endl;
		return true;
	}
	else if (!m_car.IsOnEngine())
		m_output << "Car with engine is off not set gear" << std::endl;
	else if (gear == -1 && m_car.GetSpeed() != 0)
	{
		m_output << "Car allow reverse gear only at 0 speed" << std::endl;
	}
	else if (m_car.GetDirection() == Direction::Back && m_car.GetSpeed() != 0)
	{
		m_output << "Car when driving in reverse allow set 1 gear only at 0 speed" << std::endl;
	}
	else
		m_output << "Car can not set gear to " << gear << std::endl;

	return false;
	
}
bool RemoteControl::SetSpeed(std::istream& args) 
{ 
	size_t speed;
	args >> speed;

	if (speed)
	{
		if (m_car.SetSpeed(speed))
		{
			m_output << "Car set speed " << speed << std::endl;
			return true;
		}
		else if (!m_car.IsOnEngine())
			m_output << "Car with engine off not set speed" << std::endl;
		else
			m_output << "Car can not set speed " << speed << " on " << m_car.GetGear() << " gear" << std::endl;
	}
	return false;
	
}