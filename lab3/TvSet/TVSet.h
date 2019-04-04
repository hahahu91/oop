#pragma once

class CTVSet
{
public:
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	int GetChannel() const;
	bool SelectChannel(int channel);
	bool SelectPreviousChannel();
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_prevChannel = 0;
};
