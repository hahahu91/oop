#include "pch.h"
#include "RemoteControl.h"
#include "TVSet.h"
#include <regex>
#include "Parsing.h"

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
		  { "SetChannelName", bind(&CRemoteControl::SetChannelName, this, placeholders::_1) },
		  { "GetChannelName", bind(&CRemoteControl::GetChannelName, this, placeholders::_1) },
		  { "GetChannelByName", bind(&CRemoteControl::GetChannelByName, this, placeholders::_1) },
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
	pair<int, string> parseData = ParsingNumberAndString(inputString);

	int channel = parseData.first;
	std::string channelName = parseData.second;

	string selectChannel;
	if (m_tv.IsTurnedOn())
	{
		if (channelName.empty())
		{
		
				if (m_tv.SelectChannel(channel))
				{
					selectChannel = "Channel changed to " + to_string(channel) + "\n";
					m_output << selectChannel;
					return true;
				}
				else
				{
					selectChannel = "Channel can not change to " + to_string(channel) + "\n";
					m_output << selectChannel;
					return false;
				}
		}
		else
		{
			if (m_tv.SelectChannel(channelName))
			{
				selectChannel = "Channel changed to " + channelName + "\n";
				m_output << selectChannel;
				return true;
			}
			else
			{
				selectChannel = "Channel can not change to " + channelName + "\n";
				m_output << selectChannel;
				return false;
			}
		}
	}
	else 
	{
		selectChannel = "Turned off TV not switches channel\n";
		m_output << selectChannel;
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

bool CRemoteControl::SetChannelName(std::istream& args)
{
	size_t channel;
	string nameChannel;
	args >> channel;
	getline(args, nameChannel);
	nameChannel = regex_replace(nameChannel, regex("^ +| +$|( ) +"), "$1");

	if (m_tv.IsTurnedOn())
	{
		if (m_tv.SetChannelName(channel, nameChannel))
		{
			m_output << "Channel " << to_string(channel) << " set Name " << nameChannel << "\n";
		}
	}
	else
	{
		m_output << "TV is turned off\n";
		return false;
	}
	return true;
}

bool CRemoteControl::GetChannelName(std::istream& args)
{
	size_t channel;
	args >> channel;
	if (m_tv.IsTurnedOn())
	{
		string nameChannel = m_tv.GetChannelName(channel);
		if (!nameChannel.empty())
		{
			m_output << "Channel " << to_string(channel) << " Name: " << nameChannel << "\n";
		}
	}
	else
	{
		m_output << "TV is turned off\n";
		return false;
	}
	return true;
}

bool CRemoteControl::GetChannelByName(std::istream& args)
{
	string nameChannel;
	args >> nameChannel;
	if (m_tv.IsTurnedOn())
	{
		size_t channel = m_tv.GetChannelByName(nameChannel);
		if (channel != 0)
		{
			m_output << "Channel " << nameChannel << " has number: " << to_string(channel) << "\n";
		}
	}
	else
	{
		m_output << "TV is turned off\n";
		return false;
	}
	return true;
}