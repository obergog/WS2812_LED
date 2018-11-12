#include "msp.h"
#include "led.h"

/*
 * led.c
 *
 *  Created on: Nov 10, 2018
 *      Author: alex
 */
const uint8_t period = 60;
const uint8_t logic_high_time = 34;
const uint8_t logic_low_time = 17;

//write a color to one LED
void write_led_color(uint32_t color){
    uint8_t i = 0;
    for(i = 0; i < 24; i++){
        if(color & (1 << i)){
            write_logic_high();
        }
        else{
            write_logic_low();
        }
    }
}

//write logic high
void write_logic_high(void){
#ifdef USE_SYSTICK
    SysTick->VAL = period;
    P6->OUT |= BIT0;
    while(SysTick->VAL > (period - logic_high_time));
    P6->OUT &= ~BIT0;
    while(SysTick->VAL > 0);
#endif
}

//write logic low
void write_logic_low(void){
#ifdef USE_SYSTICK
    SysTick->VAL = period;
    P6->OUT |= BIT0;
    while(SysTick->VAL > (period - logic_low_time));
    P6->OUT &= ~BIT0;
    while(SysTick->VAL > 0);
#endif
}

//hold current LED strip state
void hold_led_state(void){
    P6->OUT &= ~BIT0;
}
