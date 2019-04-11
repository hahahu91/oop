#include "pch.h"
#include "RemoteControl.h"
#include "TVSet.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "TurnOn", [this](istream& strm) { return TurnOn(strm); } },
		  { "TurnOff", bind(&CRemoteControl::TurnOff, this, _1) },
		  { "Info", bind(&CRemoteControl::Info, this, _1) },
		  { "SelectChannel", bind(&CRemoteControl::SelectChannel, this, placeholders::_1) },
		  { "SelectPreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, placeholders::_1) } })
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::TurnOn(std::istream& /*args*/)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CRemoteControl::TurnOff(std::istream& /*args*/)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CRemoteControl::Info(std::istream& /*args*/)
{
	string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\nChannel is: " + to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\n";

	m_output << info;

	return true;
}

bool CRemoteControl::SelectChannel(istream& args)
{
	string inputString;
	getline(args, inputString);
	if (int channel = atoi(inputString.c_str()))
	{
		string selectChannel;
		if (m_tv.IsTurnedOn())
		{
			if (m_tv.SelectChannel(channel))
			{
				selectChannel = "Channel changed to " + to_string(channel) + "\n";
				m_output << selectChannel;
				return true;
			}
			else
			{
				selectChannel = "Channel not can change to " + to_string(channel) + "\n";
				m_output << selectChannel;
				return false;
			}
		} 
		else
		{
			selectChannel = "Turned off TV not switches channel\n";
			m_output << selectChannel;
			return false;
		}
		
	}
	else
	{
		return false;
	}
}
bool CRemoteControl::SelectPreviousChannel(istream& args)
{
	m_tv.SelectPreviousChannel();
	string info = (m_tv.IsTurnedOn())
		? ("Channel changed to " + to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\n";

	m_output << info;

	return true;
}