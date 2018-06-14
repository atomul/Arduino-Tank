/*
 Name:		Motors.ino
 Created:	11/27/2016 11:48:20 AM
 Author:	Puiu Petre-Daniel
*/

#include <Arduino.h>

#include "HBridge.h"
#include "Tank.h"

Tank* k_tank;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);

	//////////////////////////////////
	//// H-Bridge L&R Motor pins /////
	//// device1 = Left  /////////////
	//// device2 = Right /////////////
	//////////////////////////////////
	HBridge_L293D HBridge;

	// used to PWM the motor, change the speed
	HBridge.device1.enable = 9;
	HBridge.device2.enable = 10; 

	/**
	 * Used to change direction of the motor
	 * These pins should be set as oposite from each other
	 * If both pins are HIGH or LOW, the motor will stop spinning
	 */
	HBridge.device1.input1 = 3;
	HBridge.device1.input2 = 2;

	HBridge.device2.input1 = 8;
	HBridge.device2.input2 = 11;

	//////////////////////////////////
	//// Tank ////////////////////////
	//////////////////////////////////
	k_tank = new Tank(HBridge);
}

// the loop function runs over and over again until power down or reset
void loop() {
	k_tank->Update();
}
