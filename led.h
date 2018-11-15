#include "msp.h"
#include <stdint.h>
/*
 * led.h
 *
 *  Created on: Nov 10, 2018
 *      Author: alex
 */

#ifndef LED_H_
#define LED_H_

#define USE_SYSTICK

/*
#define PERIOD 60;
#define LOGIC_HIGH_TIME 34;
#define LOGIC_LOW_TIME 17;
*/

void write_led_color(uint32_t color);
void write_logic_high(void);
void write_logic_low(void);
void hold_led_state(void);

#endif /* LED_H_ */
