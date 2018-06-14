#pragma once

#include <stdint.h>

class Button;
class SwitchButton;

class IButtonObserver
{
	friend Button;
public:
	IButtonObserver() {};

private:
	virtual void OnButtonClick(uint32_t buttonId) = 0;
	virtual void OnButtonDown(uint32_t buttonId) = 0;
	virtual void OnButtonHold(uint32_t buttonId) = 0;
	virtual void OnButtonUp(uint32_t buttonId) = 0;
};

class Button
{

public:
	Button(uint8_t inputPin);
	~Button();

	virtual void Update();

	bool IsPressed();
	bool WasPressed();

	void RegisterGeneralObserver(IButtonObserver* observer);

protected:
	virtual void OnButtonClickEvent();
	virtual void OnButtonDownEvent();
	virtual void OnButtonUpEvent();
	virtual void OnButtonHoldEvent();

private:
	Button(const Button& rhs);
	

protected:
	uint8_t	m_pin;

	int m_pressState;
	int m_previousPressState;

	IButtonObserver* m_buttonObserver;
};

