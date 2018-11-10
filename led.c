#include "msp.h"
#include "led.h"
/*
 * led.c
 *
 *  Created on: Nov 10, 2018
 *      Author: alex
 */

//write a color to one LED
void write_led(uint32_t color){

}

//write logic high
void write_logic_high(void){
    SysTick->VAL = PERIOD;
    P6->OUT |= BIT0;
    while(SysTick->VAL > (PERIOD - LOGIC_HIGH_TIME));
    P6->OUT &= ~BIT0;
    while(SysTick->VAL > 0);
}

//write logic low
void write_logic_low(void){
    SysTick->VAL = PERIOD;
    P6->OUT |= BIT0;
    while(SysTick->VAL > (PERIOD - LOGIC_LOW_TIME));
    P6->OUT &= ~BIT0;
    while(SysTick->VAL > 0);
}

//hold current LED strip state
void hold_led_state(void){
    P6->OUT &= ~BIT0;
}
