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

uint8_t high_count = 0;
uint8_t low_count = 0;

//write a color to one LED
void write_led_color(uint32_t color){
    uint8_t i = 0;
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt enabled

    for(i = 0; i < 24; i++){
        if(color & (1 << i)){

            write_logic_high();
            high_count++;
        }
        else{
            write_logic_low();
            low_count++;
        }
    }
}

//write logic high
void write_logic_high(void){
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt enabled
    TIMER_A0->CCTL[2] &= ~TIMER_A_CCTLN_CCIE;   // TACCR2 enabled

}

//write logic low
void write_logic_low(void){

}

//hold current LED strip state
void hold_led_state(void){
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled
    TIMER_A0->CCTL[2] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled
    P6->OUT &= ~BIT0;
}
