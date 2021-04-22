/*
 * File:   CCP1 (ECCP1) Echo Counter
 * Author: MBender
 *
 * Thie is the echo timer. It runs of the interal instruction clock (I_Clock)
 * It receives no interrupts. Interrupts are captured by ECCP1. 
 */

#include "Master.h"
#include "CommonRoutines.h"

void CCP1_Init(void)
{
    // Set the ECCP1 to the options selected in the User Interface
	
	// CCP1M Every falling edge; DC1B 0; P1M single; 
	CCP1CON = 0x04;    
	
	// CCPR1H 0; 
	CCPR1H = 0x00;    
	
	// CCPR1L 0; 
	CCPR1L = 0x00;    
    
    // Clear the ECCP1 interrupt flag
    PIR1bits.CCP1IF = 0;

    // Enable the ECCP1 interrupt
    PIE1bits.CCP1IE = 1;
	
	// Selecting CCPTMRS
	CCPTMRSbits.C1TSEL = 0x0;
}

void CCP1_ISR (void)
{
    PIR1bits.CCP1IF = 0;       // Clear Interrupt Flag
         // Copy captured value.
    giEchoCounter.EPl = CCPR1L;
    giEchoCounter.EPh = CCPR1H;
    CCPR1H = 0;
    CCPR1L = 0;
    Timer1_Reset();
    gb_EchoDetected = true;
}
