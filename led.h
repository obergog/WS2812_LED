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

uint16_t a_count;

//timer functions
void configure_clocks(void);
void timer_A0_config(void);
void configure_systick(void);

//led functions
void write_led_color(uint32_t color);
void write_logic_high(void);
void write_logic_low(void);
void hold_led_state(void);

#endif /* LED_H_ */
