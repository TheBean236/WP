/*
 * File:   TMR0_Code.c
 * Author: MBend
 *
 * Created on April 10, 2021, 10:40 AM
 */

#include <stdio.h>
#include <string.h>
#include "Master.h"
#include "Timer0.h"
#include "CommonRoutines.h"

bool bIncDays = false;
uint16_t imSCntr    = 0;
uint8_t iSampleCntr = 0;

// Interrupts every 5 mS
void Timer0_ISR(void) {
    TMR0H   = Timer0_Reload >> 8;
    TMR0L   = Timer0_Reload;
    INTCONbits.TMR0IF = 0;          // Reset Interrupt Flab
    
    if (Pin_Tx_Enable == 0) Pin_Tx_Enable = 1;
    if (++iSampleCntr == gcSampleRate)
    {
        iSampleCntr = 0;
        CaptureTemp();
    }
    
    if (++imSCntr == 200)       // > IF : Another second has passed
    {
        //PORTCbits.RC0 = !PORTCbits.RC0;
        gb_UpdateTime = true;
        imSCntr = 0;
    }
    return;
}

void Timer0_Init (void)
{
    TMR0H   = Timer0_Reload >> 8;
    TMR0L   = Timer0_Reload;

    INTCONbits.TMR0IF = 0;      // CLear Interrupt Flag
    INTCONbits.TMR0IE = 1;      // Enable Interrupts
    
    // T0PS 1:256; T08BIT 16-bit; T0SE Increment_Lo2Hi; T0CS FOSC/4; TMR0ON enabled; PSA assigned; 
    T0CON = 0x98;
}