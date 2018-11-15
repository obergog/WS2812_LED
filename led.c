#include "msp.h"
#include "led.h"

/*
 * led.c
 *
 *  Created on: Nov 10, 2018
 *      Author: alex
 */
const uint8_t period = 60;
const uint8_t logic_high_time = 35;
const uint8_t logic_low_time = 19;

uint8_t high_count = 0;
uint8_t low_count = 0;

//write a color to one LED
void write_led_color(uint32_t color){
    color_index = 0;
    uint8_t i = 0;
    //create array of timer values
    for(i = 0; i < 24; i++){
        if(color & (1 << i)){
            color_array[i] = logic_high_time;
        }
        else{
            color_array[i] = logic_low_time;
        }
    }
    //start the timer count value as the first in the color array
    TIMER_A0->CCR[1] = color_array[0];

    //enable timer interrupts
    __disable_irq();
    TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE;
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_CCIE;
    __enable_irq();
}

//write logic high
void write_logic_high(void){

}

//write logic low
void write_logic_low(void){

}

//hold current LED strip state
void hold_led_state(void){
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled
    P6->OUT &= ~BIT0;
}
