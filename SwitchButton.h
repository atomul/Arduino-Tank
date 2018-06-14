#pragma once

#include "Button.h"

class ISwitchButtonObserver
	//: public IButtonObserver
{
	friend SwitchButton;
public:
	ISwitchButtonObserver() {};

private:
	virtual void OnSwitchOn(uint32_t buttonId) = 0;
	virtual void OnSwitchOff(uint32_t buttonId) = 0;
};

class SwitchButton : public Button
{
public:
	SwitchButton(uint8_t inputPin);
	~SwitchButton();

	void RegisterSwitchObserver(ISwitchButtonObserver* observer);

	bool IsSwitchedOn();

private:
	void OnButtonClickEvent() override;

	ISwitchButtonObserver* m_switchButtonObserver;

	bool m_isSwitchedOn;
};