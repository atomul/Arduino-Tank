#pragma once 

#include <stdint.h>

struct HBridge_L293D
{
	/**
	 *                _______
	 *  Enable 1  1 -|  |u|  |- 16 Vcc 2
	 *  Input A1  2 -|       |- 15 Input B1
	 * Output A1  3 -|       |- 14 Output B1
	 *       GND  4 -|       |- 13 GND
	 *       GND  5 -|       |- 12 GND
	 * Output A2  6 -|       |- 11 Output B2
	 *  Input A2  7 -|       |- 10 Input B2
     *     Vcc 1  8 -|__|o|__|-  9 Enable 2
	 *
	 */

	struct Pins
	{
		uint8_t enable; //pin 1 9
		uint8_t input1; //pin 2 10
		uint8_t input2; //pin 7 15
	};

	Pins device1;
	Pins device2;
};