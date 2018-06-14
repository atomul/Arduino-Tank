#pragma once

#include <stdint.h>

#include "Button.h"
#include "SwitchButton.h"
#include "Throttle.h"

//class Button;
//class SwitchButton;

class IRemoteObserver
{
public:
	IRemoteObserver() {};

	virtual void OndButtonForwardDown() = 0;
	virtual void OndButtonForwardUp() = 0;
	virtual void OnSwitchOn() = 0;
	virtual void OnSwitchOff() = 0;

	virtual void OnSpeedChange(uint32_t speed) = 0;
};


class Remote
	: public IButtonObserver
	, public ISwitchButtonObserver
	, public IThrottleObserver
{
public:
	Remote();
	~Remote();

	void Update();

	void RegisterObserver(IRemoteObserver* observer);

private:
	void OnButtonClick(uint32_t buttonId) override final;
	void OnButtonDown(uint32_t buttonId) override final;
	void OnButtonHold(uint32_t buttonId) override final;
	void OnButtonUp(uint32_t buttonId) override final;

	void OnSwitchOn(uint32_t buttonId) override final;
	void OnSwitchOff(uint32_t buttonId) override final;

	void OnThrottleChange(uint32_t speed) override final;

private:
	SwitchButton*	m_switchButton;
	Button*			m_forwardButton;
	Throttle*		m_speedThrottle;

	IRemoteObserver*	m_observer;
};

