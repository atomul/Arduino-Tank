#pragma once

#include <stdint.h>

#include "Remote.h"
#include "HBridge.h"

class Motor;

class Tank
	: public IRemoteObserver
{
public:
	Tank(const HBridge_L293D& HBridge);
	~Tank();

	void Update();

	void OndButtonForwardDown();
	void OndButtonForwardUp();
	void OnSwitchOn();
	void OnSwitchOff();

	void OnSpeedChange(uint32_t speed);

private:

	void SetupMotors();
	void SetupRemote();

	Motor* m_motorLeft;
	Motor* m_motorRight;

	Remote* m_remote;

	uint32_t m_speed;
	uint32_t m_maxSpeed;
	uint8_t m_speedReducerScale;

	HBridge_L293D m_HBridge;
};

