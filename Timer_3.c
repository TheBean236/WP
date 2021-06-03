/*
 * File:   Timer3_SampleTimer
 * Author: MBender
 *
 * Timer 3 is currently used as a S/W module timer. It counts the number
 * of instructions between start and stop.
 * Control macros can be found in SWTimer.h
 */

#include "Master.h"
#include "SWTimer.h"

void Timer3_ISR (void)
{
    T3CONbits.TMR3ON = 0;       // Stop timer while writing
    TMR3H = 0;    
    TMR3L = 0;

    PIR2bits.TMR3IF = 0;
    return;
}

void Timer3_Init(void)
{
    // Clock source for CCP2 is ignored as CCP2 is in PWM mode
    T3CONbits.RD16      = 1;    // 16 bit
    T3CONbits.T3CCP1    = 0;    // Disable CCP2 Timer Source
    T3CONbits.T3CCP2    = 0;    // Disable CCP1 Timer Source
    T3CONbits.T3CKPS    = 0;    // Prescale 1:1
    T3CONbits.TMR3CS    = 0;    // I_Clock clock source
    T3CONbits.nT3SYNC   = 0;    // Ignored when using internal clock
    T3CONbits.TMR3ON    = 0;    // Disable timer 3

    TMR3H = 0;    
    TMR3L = 0;

    PIR2bits.TMR3IF = 0;        // Clear I/F
    PIE2bits.TMR3IE = 0;        // Disable Interrupts
}