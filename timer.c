#include "msp.h"
#include "timer.h"
/*
 * timer.c
 *
 *  Created on: Nov 10, 2018
 *      Author: alex
 */

uint16_t a_count = 0;
uint16_t b_count = 0;
uint16_t c_count = 0;


void configure_clocks(void){
    //set the core voltage higher to support higher clock frequency
    PCM->CTL0 |= PCM_CTL0_AMR__AM_LDO_VCORE1;
    FLCTL->BANK0_RDCTL |= FLCTL_BANK0_RDCTL_WAIT2;
    FLCTL->BANK1_RDCTL |= FLCTL_BANK1_RDCTL_WAIT2;

    //set the SMLK clock to 48MHz
    CS->KEY = 0x695A;
    CS->CTL0 = 0;
    CS->CTL0 |= CS_CTL0_DCORSEL_5;   //set frequency range to 32 to 64 MHz
    CS->CTL1 |= CS_CTL1_DIVS_0;      //clock divider for SMCLK is 1 (48MHz)
    CS->CTL1 |= CS_CTL1_DIVHS__2;      //clock divider for HSMCLK is 4 (12MHz)
    CS->KEY = 0;
}

void timer_A0_config(void){
    TIMER_A0->R = 0;         // Reset count
    //Use SMCLK, Up mode, divide clock by 1, enable interrupts
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID_0 | TIMER_A_CTL_IE;
    TIMER_A0->CCR[0] = 60;      //Total period = 1.25us
    TIMER_A0->CCR[1] = 17;      //time for logic 0 = .35us
    TIMER_A0->CCR[2] = 34;      //time for logic 1 = .7us
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled
    TIMER_A0->CCTL[2] &= ~TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt disabled

    /* Enable Interrupts in the NVIC */
    NVIC_EnableIRQ(TA0_0_IRQn);
}

void configure_systick(void){
    SysTick->CTRL = 0x05;
    SysTick->LOAD = 0x0060;
}

void TA0_0_IRQHandler(void){

    if(TIMER_A0->CCTL[0] & BIT0){
        P6->OUT |= BIT0;            //write the pin high at beginning of cycle
        a_count++;
        TIMER_A0->CCTL[0] &= ~BIT0;
        TIMER_A0->R = 0;
    }
    //for logic low
    if(TIMER_A0->CCTL[1] & BIT0){
        P6->OUT &= ~BIT0;            //write the pin low for logic low
        b_count++;
        TIMER_A0->CCTL[1] &= ~BIT0;
    }
    //for logic high
    if(TIMER_A0->CCTL[2] & BIT0){
        P6->OUT &= ~BIT0;            //write the pin low for logic high
        c_count++;
        TIMER_A0->CCTL[2] &= ~BIT0;
    }
}
