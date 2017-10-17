/*
 * RotaryEncoderWithButton
 *
 *  Created on: Aug 9, 2014
 *      Author: Konstantin Gredeskoul
 *
 *  (c) 2014 All rights reserved.  Please see LICENSE.
 *
 *  Example of such Rotary Encoder is this one:
 *  https://www.adafruit.com/products/377
 *
 */

#ifndef RotaryEncoderWithButton_H_
#define RotaryEncoderWithButton_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif

#include <Encoder.h>

#define DEBOUNCE_DELAY 		50

// once you press the button, no other events to the button matter
// until this time has passed.
#define BUTTON_PRESS_DELAY 300

class RotaryEncoderWithButton {
public:
	RotaryEncoderWithButton(uint8_t rotaryPinA, uint8_t rotaryPinB, uint8_t buttonPin);
	void begin();
	bool buttonClicked();
	uint32_t rotaryDelta();

	Encoder *encoder;
private:
	uint8_t _rotaryPinA, _rotaryPinB, _buttonPin;
	bool _hasNotReadRotary;
	unsigned long int _lastButtonPressedAt;
	signed long int _lastRotaryValue;
};

#endif /* RotaryEncoderWithButton_H_ */
