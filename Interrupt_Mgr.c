/*
 * File:   Interrupt_Mgr
 * Author: MBender
 *
 * This is the first interrupt routine. It decodes the interrupt and calls
 * the appropriate ISR. Sequence is important. 
 * 
 * Priority interrupts are disabled. so everything is on the same priority
 */

#include <xc.h>
#include "Master.h"
#include "CommonRoutines.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        Timer0_ISR();       // Time-of-Day Clock
    }
    else if(INTCONbits.PEIE == 1)
    {
        if(PIE2bits.TMR3IE == 1 && PIR2bits.TMR3IF == 1)
        {
            Timer3_ISR();   // Sample Timer
        } 
        else if(PIE1bits.CCP1IE == 1 && PIR1bits.CCP1IF == 1)
        {
            CCP1_ISR();     // Echo Received Interrupt
        } 
        else if(PIE1bits.TMR2IE == 1 && PIR1bits.TMR2IF == 1)
        {
            Timer2_ISR();   // 40Khz Interrupt
        } 
        else
        {
            //Unhandled Interrupt
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}
