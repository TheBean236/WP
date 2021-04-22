
#include "Master.h"
#include "Timer2.h"
#include "CommonRoutines.h"

void StartDepthDetection (void);
void EndDepthDetection(void);

void Timer2_ISR (void)
{
    // Timer 2 interrupts when N pulses are sent to the transmitter
    // Reset Timer2
    T2CONbits.TMR2ON = 0;   // Turn the timer off
    TMR2 = 0;               // Clear the Counter
    PIE1bits.TMR2IE = 0;    // Disable Timer 2 Interrupts
    PIR1bits.TMR2IF = 0;    // Clear the interrupt flag
}

void StartDepthDetection(void)
{
    // Clear counters for CCP1
    // Initialize Timer2 and CCP2
    // Enable Interrupts for Timer 2
    // Activate Transmit Enable Pin
    Pin_Tx_Enable = 0;
    // Start Timer 2
    PIR1bits.TMR2IF = 0;    // Clear the interrupt flag
    PIE1bits.TMR2IE = 1;    // Enable Interrupts
    T2CONbits.TMR2ON = 1;   // Start the timer
    T1CONbits.TMR1ON = 1;   // Start Timer 1
}

void EndDepthDetection(void)
{
}

void Timer2_Init(void)
{
    // Period Register (# of after-PreScale Ticks) 
    PR2 = PR2_Val;          // Set Period Register

    // TMR2 0; 
    TMR2 = 0x00;            // Clear the counter
    PIR1bits.TMR2IF = 0;    // Clear the interrupt flag
    PIE1bits.TMR2IE = 0;    // Disable Interrupts
    T2CON = (T2_NumPulses-2)<<3 | 0 | 0; // Num Pulses + T2Off + Prescale 1
}
