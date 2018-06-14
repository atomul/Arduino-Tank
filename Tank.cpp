#include "Tank.h"

#include "HBridge.h"
#include "Motor.h"

#include <Arduino.h>

Tank::Tank(const HBridge_L293D& HBridge)
	: m_speed(0)
	, m_speedReducerScale(2)
	, m_maxSpeed(255 / m_speedReducerScale)
{
	m_HBridge = HBridge;

	SetupRemote();
	SetupMotors();
}

Tank::~Tank()
{
}

void Tank::SetupRemote()
{
	m_remote = new Remote();
	m_remote->RegisterObserver(this);
}

void Tank::SetupMotors()
{
	m_motorLeft = new Motor();
	m_motorRight = new Motor();

	m_motorLeft->AssignHBridge(m_HBridge.device1.enable, m_HBridge.device1.input1, m_HBridge.device1.input2);
	m_motorRight->AssignHBridge(m_HBridge.device2.enable, m_HBridge.device2.input1, m_HBridge.device2.input2);
}

void Tank::Update()
{
	m_remote->Update();
	m_motorLeft->Update();
	m_motorRight->Update();
}

void Tank::OndButtonForwardDown()
{
	Serial.print("cave");
	m_motorLeft->Enable();
	m_motorRight->Enable();
}

void Tank::OndButtonForwardUp()
{
	m_motorLeft->Disable();
	m_motorRight->Disable();
}

void Tank::OnSwitchOn()
{
	m_motorLeft->Enable();
	m_motorRight->Enable();
}

void Tank::OnSwitchOff()
{
	m_motorLeft->Disable();
	m_motorRight->Disable();
}

void Tank::OnSpeedChange(uint32_t speed)
{
	m_speed = speed / 4 / m_speedReducerScale;

	int halfMaxSpeed = (m_maxSpeed / 2) - 1; // -1 because it's an odd number

	int leftSpeed = 0;
	int rightSpeed = 0;
	if (m_speed < halfMaxSpeed)
	{
		leftSpeed = m_speed * 2;
		rightSpeed = m_maxSpeed;
	}
	else if (m_speed > halfMaxSpeed)
	{
		leftSpeed = m_maxSpeed;
		rightSpeed = (m_maxSpeed - m_speed) * 2;
	}
	else
	{
		leftSpeed = m_maxSpeed;
		rightSpeed = m_maxSpeed;
	}

	Serial.print("Speed: ");
	Serial.print(m_speed);
	Serial.print(" Left: ");
	Serial.print(leftSpeed);
	Serial.print(" Right: ");
	Serial.print(rightSpeed);
	Serial.print("\n");
	m_motorLeft->SetSpeed(leftSpeed);
	m_motorRight->SetSpeed(rightSpeed);
}
