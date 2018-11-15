#include "msp.h"
#include "core_cm4.h"
#include "timer.h"
#include <stdint.h>
#include "led.h"

/**
 * main.c
 */

#define ENABLE_SLEEPONEXIT (0x00000002)

//#define USE_SYSTICK
#define USE_TIMER
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	__disable_irq();
	configure_clocks();
	timer_A0_config();
	configure_systick();

    //enable P6.0 as an output pin to drive the LED
    P6->SEL0 &= ~BIT0;
    P6->SEL1 &= ~BIT0;
    P6->DIR |= BIT0;
    P6->OUT &= ~BIT0;


    //enable timer interrupts

    __enable_irq();                //enable global interupts

    SCB->SCR &= ~ENABLE_SLEEPONEXIT;            //wake up on exit from ISR

    //write_led_color(0x00FF00);
    //write_led_color(0x0000FF);
    //hold_led_state();
    while(1){
        if(a_count > 24){
            __disable_irq();
            TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled
        }
        hold_led_state();

    }
}
