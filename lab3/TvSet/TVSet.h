#pragma once
#include <map>

class CTVSet
{
public:
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();

	const size_t GetChannel() const;
	const std::string GetChannelName(const size_t channel);
	const size_t GetChannelByName(const std::string& nameChannel);
	bool SelectChannel(size_t channel);
	bool SelectChannel(const std::string& nameChannel);
	bool SelectPreviousChannel();
	bool DeleteChannelName(const std::string& channelName);

	bool SetChannelName(size_t channel, const std::string& nameChannel);

private:
	bool m_isOn = false;
	size_t m_selectedChannel = 1;
	size_t m_prevChannel = 1;
	std::map<size_t, std::string> m_channelNames;
	std::map<std::string, size_t> m_channelByName;
};
