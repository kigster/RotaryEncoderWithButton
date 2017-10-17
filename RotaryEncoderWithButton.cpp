/*
 * RotaryEncoderWithButton.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: Konstantin Gredeskoul
 *
 *  (c) 2014 All rights reserved.  Please see LICENSE.
 */

#include "RotaryEncoderWithButton.h"

RotaryEncoderWithButton::RotaryEncoderWithButton(
		uint8_t rotaryPinA,
		uint8_t rotaryPinB,
		uint8_t buttonPin) {

	_lastButtonPressedAt = 0;
	_rotaryPinA = rotaryPinA;
	_rotaryPinB = rotaryPinB;
	_buttonPin = buttonPin;
	_hasNotReadRotary = true;
	encoder = new Encoder(rotaryPinA, rotaryPinB);
}

void RotaryEncoderWithButton::begin() {
	pinMode(_rotaryPinA, INPUT);
	pinMode(_rotaryPinB, INPUT);
	pinMode(_buttonPin, INPUT);
	digitalWrite(_rotaryPinA, HIGH);
	digitalWrite(_rotaryPinB, HIGH);
	digitalWrite(_buttonPin, HIGH);
}

uint32_t RotaryEncoderWithButton::rotaryDelta() {
	uint32_t knobValue = encoder->read();
	if (_hasNotReadRotary) {
		_lastRotaryValue = knobValue;
		_hasNotReadRotary = false;
	}

	uint32_t delta = _lastRotaryValue - knobValue;
	_lastRotaryValue = knobValue;
	return delta;
}

bool RotaryEncoderWithButton::buttonClicked() {
	bool currentState;
	bool previousState;
	bool pressed = false;

	if (millis() - _lastButtonPressedAt < BUTTON_PRESS_DELAY)
		return false;

	previousState = currentState = digitalRead(_buttonPin);      // store switch state
	for (int counter = 0; counter < DEBOUNCE_DELAY; counter++) {
		delay(1); // wait for 1 millisecond
		currentState = digitalRead(_buttonPin);  // read the pin
		if (currentState != previousState) {
			pressed = true;
			_lastButtonPressedAt = millis();
			//counter = 0; // reset the counter if the state changes
			previousState = currentState;  // and save the current currentState
		}
	}

	// here when the switch currentState has been stable longer than the debounce period
	return pressed;
}
