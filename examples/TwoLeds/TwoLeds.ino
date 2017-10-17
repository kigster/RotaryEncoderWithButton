/*
 * TwoLeds – this example demonstrates using RotaryEncoder with a button.
 *
 * Dependencies for the library:
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * Dependencies for the example:
 *
 * RotaryEncoderWithButton library
 * SimpleTimer library
 *
 *  Created on: Aug 9, 2014
 *      Author: Konstantin Gredeskoul
 *
 *  (c) 2014 All rights reserved.  Please see LICENSE.
 */

#include "printf.h"
#include "BlinkingLed.h"

#include <RotaryEncoderWithButton.h>
#include <SimpleTimer.h>

SimpleTimer timer(1);
//RotaryEncoderWithButton rotary(2,3,4);
RotaryEncoderWithButton rotary(A5,2,A4);

const short elements = 2;
blinkingLed led[elements];
uint8_t currentElementIndex = 0;
int i;

//_________________________________________________________________________________________

void blinkLeds() {
	unsigned long now = millis();
	for (i = 0; i < elements; i++) {
		blinkingLed *thisLed = &led[i];
		if (i == currentElementIndex) {
			if (now - thisLed->stateChangedAt > thisLed->freq) {
				thisLed->on = !(thisLed->on);
				thisLed->stateChangedAt = now;
				digitalWrite(thisLed->pin, thisLed->on);
			}
		} else {
			digitalWrite(thisLed->pin, LOW);
		}
	}
}

void setFrequencyFromEncoder() {
	long newFreq = rotary.rotaryDelta() + led[currentElementIndex].freq;
	led[currentElementIndex].freq = constrain(newFreq, 1, 1000);
}

void swapLedsIfButtonPressed() {
	if (rotary.buttonClicked()) {
		currentElementIndex++;
		currentElementIndex = currentElementIndex % elements;
		printf("INFO: a rotary button was pressed, current index is now [%d]\n",
				currentElementIndex);
	}
}

void printStatus(int timerId) {
	printf("INFO: encoder read out: [%5d], current LED: [%d], LEDs frequencies: [%3d, %3d]\n",
			(int) rotary.encoder->read(),
			currentElementIndex,
			led[0].freq,
			led[1].freq);
}

//_________________________________________________________________________________________

void setup() {
	Serial.begin(115200);
	printf_begin();

	rotary.begin();

	led[0].pin = 7;
	led[1].pin = 6;

	printf("\n\nRotary Encoder Example\n");
	printf("Connect leds to pins [%d] and [%d]\nClick to swap LEDs, turn knob to change frequency.\n",
			led[0].pin, led[1].pin);

	for (i = 0; i < elements; i++) {
		pinMode(led[i].pin, OUTPUT);
		led[i].freq = 100;
		led[i].on = false;
		led[i].stateChangedAt = 0;
	}

	timer.setInterval(1000, &printStatus);
}

void loop() {
	setFrequencyFromEncoder();
	swapLedsIfButtonPressed();
	blinkLeds();

	timer.run();
}
