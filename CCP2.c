/*
 * File:   CCP2 PWM - 40Khz Generator
 * Author: MBender
 *
 * THis is the PWM for the 40Khz clock. 
 * Timer2 is the source. It takes 50 pulses for a full cycle.
 * The PWM module counts half (-1) and switches generating a 40Khz
 * square wave with a 50% duty cycle. 
 * 
 * Once initialized, CCP2 never changes. It starts and stops based on
 *   Timer2 counts. 
 * 
 * No Interrupt. Timer2 gets the interrupt to stop transmission. 
 */

#include "Master.h"
#include "CommonRoutines.h"
// PWM uses primary clod (C_Clock_ not I_Clock)
// Enter Period count - 1
#define  CCP2PWM_Ticks  99

void CCP2_Init (void)
{
    // Set the PWM2 to the options selected in the User Interface
	
	// CCP2M PWM; DC2B 3; 
	CCP2CON = 0x0C;     
	CCPR2L = CCP2PWM_Ticks>>2;   // 24 = 25 pulses - 1 = (Pulses/Cycle / 2) - 1
    CCP2CONbits.DC2B = CCP2PWM_Ticks && 0x03;
	CCPR2H = 0x00;   // 0
}
