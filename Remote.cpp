#include "Remote.h"

#include <Arduino.h>

#include "Button.h"
#include "SwitchButton.h"

#include "Tank.h"

const uint8_t k_pin_button_enable = 4;
const uint8_t k_pin_button_forward = 5;

const uint8_t k_pin_throttle_speed = A0;
const uint8_t k_throttle_threshold = 2;

bool IsButtonEnable(uint8_t buttonPin)
{
	return (k_pin_button_enable == buttonPin);
}

bool IsButtonForward(uint8_t buttonPin)
{
	return (k_pin_button_forward == buttonPin);
}

Remote::Remote()
{
	m_switchButton = new SwitchButton(k_pin_button_enable);
	m_forwardButton = new Button(k_pin_button_forward);

	m_speedThrottle = new Throttle(k_pin_throttle_speed, k_throttle_threshold);

	m_forwardButton->RegisterGeneralObserver(this);

	m_switchButton->RegisterGeneralObserver(this);
	m_switchButton->RegisterSwitchObserver(this);

	m_speedThrottle->RegisterObserver(this);
}


Remote::~Remote()
{
	delete m_switchButton;
	m_switchButton = NULL;
}

void Remote::Update()
{
	m_switchButton->Update();
	m_speedThrottle->Update();
	m_forwardButton->Update();
}

void Remote::RegisterObserver(IRemoteObserver * observer)
{
	m_observer = observer;
}

void Remote::OnButtonClick(uint32_t buttonId)
{
	Serial.print("Button Pressed\n");
	//int motorSpeed = analogRead()
}

void Remote::OnButtonDown(uint32_t buttonId)
{
	Serial.print("Button Down\n");
	if (IsButtonForward(buttonId))
	{
		m_observer->OndButtonForwardDown();
	}
}

void Remote::OnButtonHold(uint32_t buttonId)
{
	//Serial.print("Button Hold\n");
}

void Remote::OnButtonUp(uint32_t buttonId)
{
	if (IsButtonForward(buttonId))
	{
		m_observer->OndButtonForwardUp();
	}
}

void Remote::OnSwitchOn(uint32_t buttonId)
{
	Serial.print("Switch On\n");
	if (IsButtonEnable(buttonId))
	{
		m_observer->OnSwitchOn();
	}
}

void Remote::OnSwitchOff(uint32_t buttonId)
{
	Serial.print("Switch Off\n");
	if (IsButtonEnable(buttonId))
	{
		m_observer->OnSwitchOff();
	}
}

void Remote::OnThrottleChange(uint32_t speed)
{
	//Serial.print("Throttle changed: ");
	//Serial.print(speed);
	//Serial.print("\n");

	m_observer->OnSpeedChange(speed);
}
