/*
 * File:   Timer3_SampleTimer
 * Author: MBender
 *
 * This timer is for testing only. It fires approximately ever 20 ms
 *      so we can see the progress of the echo mechanism on the scope. 
 * Created on April 10, 2021, 10:40 AM
 */

#include "Master.h"
#include "CommonRoutines.h"

// We divide by 1000 as I_Clock is in Seconds and T3_Period is in mS
uint16_t    Timer3_Reload = ~((I_Clock / 1000) / T3_Prescale * (T3_Period));
bool        Timer3_Sampling = true;
uint16_t    Timer3_Cntr = 0;

//Test

void Timer3_ISR (void)
{
    Timer3_Cntr ++;
    T3CONbits.TMR3ON = 0;       // Stop timer while writing
    TMR3H = (uint8_t)(Timer3_Reload>>8);    
    TMR3L = (uint8_t) Timer3_Reload;
    T3CONbits.TMR3ON = 1;       // ... and restart it. 
    
    PIR2bits.TMR3IF = 0;
    
    if (Timer3_Sampling)
    {
        if (Timer3_Cntr >= 2) 
        {
            Timer3_Sampling = false;
            Pin_Tx_Enable = 1;
        }
    }
    if (Timer3_Cntr >= T3_SampeRate)
    {
        Timer3_Sampling = true;
        Timer3_Cntr = 0;
        StartDepthDetection();
    }
}

void Timer3_Init(void)
{
//T3GSS T3G_pin; TMR3GE disabled; T3GTM disabled; T3GPOL low; T3GGO done; T3GSPM disabled; 
    //Load Timer 3 Registers 
    TMR3H = (uint8_t) (Timer3_Reload >> 8);
    TMR3L = (uint8_t) Timer3_Reload;

    PIR2bits.TMR3IF = 0;        // Clear I/F

    // T3CKPS 1:8; T3OSCEN disabled; T3SYNC synchronize; TMR3CS FOSC/4; TMR3ON enabled; T3RD16 enabled; 
    T3CON = 0x33;
    PIE2bits.TMR3IE = 1;
}