/*
 * BlinkingLed.h
 *
 *  Created on: Aug 9, 2014
 *      Author: Konstantin Gredeskoul
 *
 *  (c) 2014 All rights reserved.  Please see LICENSE.
 */

#ifndef BLINKINGLED_H_
#define BLINKINGLED_H_

typedef struct blinkingLedStruct {
	int pin;
	unsigned int freq;
	unsigned long stateChangedAt;
	bool on;
} blinkingLed;


#endif /* BLINKINGLED_H_ */
