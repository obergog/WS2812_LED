#include "msp.h"
#include "timer.h"
#include <stdint.h>
#include "led.h"

/**
 * main.c
 */

#define USE_SYSTICK
//#define USE_TIMER
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	configure_clocks();
	timer_A0_config();
	configure_systick();

    //enable P6.0 as an output pin to drive the LED
    P6->SEL0 &= ~BIT0;
    P6->SEL1 &= ~BIT0;
    P6->DIR |= BIT0;
    P6->OUT &= ~BIT0;

    __enable_irq();                //enable global interupts

    //enable timer interrupts
#ifdef USE_TIMER
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;
    TIMER_A0->CCTL[2] &= ~TIMER_A_CCTLN_CCIE;
#endif USE_TIMER

    while(1){
#ifdef USE_SYSTICK
        SysTick->VAL = 60;
        P6->OUT |= BIT0;
        while(SysTick->VAL > (60-34));
        P6->OUT &= ~BIT0;
        while(SysTick->VAL > 0);
#endif
    }
}
