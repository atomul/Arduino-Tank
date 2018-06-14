#pragma once

#include <stdint.h>

class Motor
{
	enum MotorDirection
	{
		MOTOR_DIRECTION_FORWARD,
		MOTOR_DIRECTION_BACKWARD
	};

public:
	Motor();
	~Motor();

	void Update();

	void SetDirection(const MotorDirection direction);
	void SetSpeed(const uint32_t m_motorSpeed);

	bool IsEnabled();

	void Enable();
	void Disable();

	// ToDo 2PD: Create a struct for H-Bridge
	void AssignHBridge(uint8_t enablePin, uint8_t directionPin2, uint8_t directionPin7);

private:
	MotorDirection m_direction;
	uint32_t m_speed;
	bool m_isEnabled;

	////////////////////////
	/// H-Bridge pins //////
	////////////////////////

	// used to PWM the motor, change the speed
	uint8_t m_pin_hbridge_enable = 9;

	/**
	* Used to change direction of the motor
	* These pins should be set as oposite from each other
	* If both pins are HIGH or LOW, the motor will stop spinning
	*/
	uint8_t m_pin_hbridge_directionForward = 2;
	uint8_t m_pin_hbridge_directionBackward = 3;
};