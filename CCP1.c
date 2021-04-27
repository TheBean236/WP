/*
 * File:   CCP1 (ECCP1) Echo Counter
 * Author: MBender
 *
 * Thie is the echo timer. It runs of the interal instruction clock (I_Clock)
 * It receives no interrupts. Interrupts are captured by ECCP1. 
 */

#include "Master.h"
#include "CommonRoutines.h"
#include "CCP1.h"

void CCP1_Init(void)
{
	// CCP1M Every falling edge; DC1B 0; P1M single; 
    // CCP1CON for 45K50 and 2455 are the same
	CCP1CON = CCP1CON_Disable;    
	
	CCPR1H = 0x00;      // Initialize counter to zero
	CCPR1L = 0x00;    
    
    PIR1bits.CCP1IF = 0;    // Reset Interrupt Flag
    PIE1bits.CCP1IE = 0;    // Enable Interrupt
	
#ifdef _18F45K50
    // 2455 does not have a CCPTRMS register
    // Assignment is in the T3CON register
	CCPTMRSbits.C1TSEL = 0x0;
#endif
}

void CCP1_ISR (void)
{
    // Copy captured value.
    giEchoCounter.EPl = CCPR1L;
    giEchoCounter.EPh = CCPR1H;
    // THe 25K50 loads the counter from TMR1. THe 2455 does not. CCP1 does the counting
#ifdef _18F2455
	CCP1CON = CCP1CON_Disable;   // 2455 clears CCP1M4:0 bits reset 
    CCPR1H = 0;
    CCPR1L = 0;
#endif
    PIR1bits.CCP1IF = 0;        // Clear Interrupt Flag
    PIE1bits.CCP1IE = 0;        // Disable interrupts on CCP1
    Timer1_Reset();
    gb_EchoDetected = true;
}

void CCP1_Activate()
{
    CCPR1H = 0;
    CCPR1L = 0;
    CCP1CON = CCP1CON_Enable;
    PIR1bits.CCP1IF = 0;       // Clear Interrupt Flag
    PIE1bits.CCP1IE = 1;
}
