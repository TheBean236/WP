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
bool        Timer3_Sampling = false;
uint16_t    Timer3_Cntr = 0;

//Test

void Timer3_ISR (void)
{
    T3CONbits.TMR3ON = 0;       // Stop timer while writing
    TMR3H = (uint8_t)(Timer3_Reload>>8);    
    TMR3L = (uint8_t) Timer3_Reload;

    PIR2bits.TMR3IF = 0;
    return;
    //
    // We've switched the sample timer to TMR0. THis timer is 
    // not used anymore 
    //
}

void Timer3_Init(void)
{
#ifdef _18F45K50
    // T3CKPS 1:8; T3OSCEN disabled; T3SYNC synchronize; TMR3CS FOSC/4; TMR3ON enabled; T3RD16 enabled; 
    T3CON = 0x33;
#endif 
#ifdef _18F2455
    // 1 0 1 1   1 0 0 1
    T3CON = 0xb9;
#endif

    //Pin_Tx_Enable = 1;
    //Load Timer 3 Registers 
    TMR3H = (uint8_t)(Timer3_Reload>>8);    
    TMR3L = (uint8_t) Timer3_Reload;

    PIR2bits.TMR3IF = 0;        // Clear I/F
    PIE2bits.TMR3IE = 0;
}