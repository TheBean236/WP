/*
 * File:   TMR1.c
 * Author: MBender
 *
 * Created on April 10, 2021, 10:40 AM
 */

#include "Master.h"

void Timer1_Init()
{
    PIR1bits.TMR1IF = 0;    // Clear Interrupt Flag
    PIE1bits.TMR1IE = 0;    // Disable Interrupts
    
#ifdef _18F45K50
    T1CON   = 0x02;     // 16 Bit, 1:1,  Osc Off, Synch, I_Clock
    T1GCON  = 0;        // 16 Bit, Fosc4, Osc off, Synch 
#endif
#ifdef  _18F2455
    T1CON   = 0x80;     // 16-bit, Fosc4, Synch, Osc off, TMR1 Disabled
#endif
    TMR1H = 0;
    TMR1L = 0;
}

void Timer1_Reset()
{
    T1CONbits.TMR1ON = 0;
    TMR1H = 0;
    TMR1L = 0;
}

void Timer1_ISR()
{
    // Do Nothing... 
    //Timer 1 is a counter for CCP1 which handles the interrupt
    Nop();      // In case we need a breakpoint
}