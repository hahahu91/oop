#include "pch.h"
#include "TVSet.h"
#include "Reduce.h"

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

const size_t CTVSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

const std::string CTVSet::GetChannelName(size_t channel)
{
	if (m_isOn && channel >= 1 && channel <= 99)
	{
		std::map<size_t, std::string>::iterator it;
		it = m_channelNames.find(channel);
		if (it != m_channelNames.end())
		{
			return it->second;
		}
	}
	return "";
}

const size_t CTVSet::GetChannelByName(const std::string& nameChannel)
{
	if (m_isOn)
	{
		std::map<std::string, size_t>::iterator it;
		it = m_channelByName.find(nameChannel);
		if (it != m_channelByName.end())
		{
			return it->second;
		}
	}
	return 0;
}

bool CTVSet::SelectChannel(size_t channel)
{
	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
	if (isAvailableChannel && m_isOn)
	{
		m_prevChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}
	return false;
}
bool CTVSet::SelectChannel(const std::string& channelName)
{
	return SelectChannel(GetChannelByName(channelName));
}
bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	if (m_isOn && !channelName.empty())
	{
		std::map<std::string, size_t>::iterator it;
		it = m_channelByName.find(channelName);
		if (it != m_channelByName.end())
		{
			m_channelNames[GetChannelByName(channelName)].erase();
			m_channelByName.erase(it);
			return true;
		}
	}
	return false;
}

bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn)
	{
		std::swap(m_selectedChannel, m_prevChannel);
		return true;
	}
	return false;
};

bool CTVSet::SetChannelName(size_t channel, const std::string& nameChannel)
{
	if (channel >= 1 && channel <= 99 && m_isOn)
	{
		if (!nameChannel.empty())
		{
			std::string newName = reduce(nameChannel);
			DeleteChannelName(newName);
			m_channelNames[channel] = newName;
			m_channelByName[newName] = channel;
			return true;
		}
	}
	return false;
}
