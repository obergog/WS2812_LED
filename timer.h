#include "msp.h"
/*
 * timer.h
 *
 *  Created on: Nov 10, 2018
 *      Author: alex
 */
uint16_t a_count;

#ifndef TIMER_H_
#define TIMER_H_

void configure_clocks(void);
void timer_A0_config(void);
void configure_systick(void);

#endif /* TIMER_H_ */
