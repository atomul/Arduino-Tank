#include "Motor.h"

#include <Arduino.h>

Motor::Motor()
	: m_direction(MOTOR_DIRECTION_FORWARD)
	, m_speed(0)
	, m_isEnabled(false)
{}

Motor::~Motor()
{}

void Motor::Update()
{
	if (IsEnabled())
	{
		if (m_direction == MOTOR_DIRECTION_FORWARD)
		{
			digitalWrite(m_pin_hbridge_directionForward, HIGH);
			digitalWrite(m_pin_hbridge_directionBackward, LOW);
		}
		else
		{
			digitalWrite(m_pin_hbridge_directionForward, LOW);
			digitalWrite(m_pin_hbridge_directionBackward, HIGH);
		}

		analogWrite(m_pin_hbridge_enable, m_speed);
		//Serial.print("Speed: ");
		//Serial.print(m_speed);
		//Serial.print("\n");
	}
}

void Motor::SetDirection(const MotorDirection direction) { m_direction = direction; }
void Motor::SetSpeed(const uint32_t speed) { m_speed = speed; }
bool Motor::IsEnabled() { return m_isEnabled; }

void Motor::Enable() { m_isEnabled = true; }

void Motor::Disable()
{
	analogWrite(m_pin_hbridge_enable, 0);
	m_isEnabled = false;
}

void Motor::AssignHBridge(uint8_t enablePin, uint8_t directionPin2, uint8_t directionPin7)
{
	m_pin_hbridge_enable = enablePin;
	m_pin_hbridge_directionForward = directionPin2;
	m_pin_hbridge_directionBackward = directionPin7;

	pinMode(m_pin_hbridge_enable, OUTPUT);
	pinMode(m_pin_hbridge_directionForward, OUTPUT);
	pinMode(m_pin_hbridge_directionBackward, OUTPUT);
}
