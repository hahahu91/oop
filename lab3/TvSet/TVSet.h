#pragma once
#include <map>

class CTVSet
{
public:
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();

	int GetChannel() const;
	std::string GetChannelName(const size_t channel);
	size_t GetChannelByName(const std::string& nameChannel);
	bool SelectChannel(int channel);
	bool SelectChannel(const std::string nameChannel);
	bool SelectPreviousChannel();
	bool DeleteChannelName(const std::string channelName);

	bool SetChannelName(size_t channel, const std::string & nameChannel);

private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_prevChannel = 0;
	std::map<size_t, std::string> m_channelNames;
	std::map<std::string, size_t> m_channelByName;
};
