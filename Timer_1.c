/*
 * File:   TMR0_Code.c
 * Author: MBend
 *
 * Created on April 10, 2021, 10:40 AM
 */

#include "Master.h"

#ifdef __18F45K50__
#define setT1Gate
#endif

void Timer1_Init()
{
    PIR1bits.TMR1IF = 0;    // Clear Interrupt Flag
    PIE1bits.TMR1IE = 0;    // Disable Interrupts
    T1CON       = 0x02;     // 16 Bit, 1:1,  Osc Off, Synch, I_Clock
#ifdef setT1Gate
    T1GCON      = 0;
#endif
    TMR1H       = 0;
    TMR1L       = 0;
}

void Timer1_Reset()
{
    T1CONbits.TMR1ON = 0;
    TMR1H   = 0;
    TMR1L   = 0;
}

void Timer1_ISR()
{
    // Do Nothing... 
    //Timer 1 is a counter for CCP1 which handles the interrupt
}