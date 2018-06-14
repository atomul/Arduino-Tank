#include "Button.h"

#include <Arduino.h>

Button::Button(uint8_t pin)
{
	m_pressState = 0;
	m_previousPressState = 0;

	m_pin = pin;
	pinMode(m_pin, INPUT);
}

Button::~Button()
{
}

void Button::Update()
{
	m_pressState = digitalRead(m_pin);

	if (IsPressed())
	{
		// it was pressed earlier and still holding
		if (WasPressed())
		{
			OnButtonHoldEvent();
		}
		// it was just pressed
		else
		{
			OnButtonDownEvent();
		}
	}
	else
	{
		// if it was pressed earlier and not it isn't it was just released
		if (WasPressed())
		{
			OnButtonUpEvent();
			OnButtonClickEvent();
		}
	}

	m_previousPressState = m_pressState;
}

void Button::RegisterGeneralObserver(IButtonObserver* observer)
{
	if (m_buttonObserver)
	{
		m_buttonObserver = observer;
	}
}

void Button::OnButtonClickEvent()
{
	if (m_buttonObserver)
	{
		m_buttonObserver->OnButtonClick(m_pin);
	}
}

void Button::OnButtonDownEvent()
{
	if (m_buttonObserver)
	{
		m_buttonObserver->OnButtonDown(m_pin);
	}
}

void Button::OnButtonUpEvent()
{
	if (m_buttonObserver)
	{
		m_buttonObserver->OnButtonUp(m_pin);
	}
}

void Button::OnButtonHoldEvent()
{
	if (m_buttonObserver)
	{
		m_buttonObserver->OnButtonHold(m_pin);
	}
}

bool Button::IsPressed() { return m_pressState; }
bool Button::WasPressed() { return m_previousPressState; }
