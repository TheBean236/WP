
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

    TMR2            = 0;    // Clear the counter
    PIE1bits.TMR2IE = 0;    // Disable Timer 2 Interrupts
    PIR1bits.TMR2IF = 0;    // Clear the interrupt flag
}

void StartDepthDetection(void)
{
    // Clear counters for CCP1
    // Initialize Timer2 and CCP2
    // Enable Interrupts for Timer 2
    // Start Timer 2
    TMR2 = 0;                   // Ensure starting at zero
    PIR1bits.TMR2IF     = 0;    // Clear TMR2 interrupt flag
    PIE1bits.TMR2IE     = 1;    // Enable TMR2 Interrupts
    T2CONbits.TMR2ON    = 1;    // Start TMR2   
    CCP1_Activate();            // Activate CCP1 - Capture TMR1 clock
    T1CONbits.TMR1ON    = 1;    // Start TMR1
}

void Timer2_Init(void)
{
    // Period Register (# of after-PreScale Ticks) 
    PR2 = PR2_Val;          // Set Period Register
    // NOTE: T2CON is the same for 45K50 and 2455
#ifdef _18F45K50
    T2CON = (T2_NumPulses-2)<<3 | 0 | 0; // Num Pulses + T2Off + Prescale 1
#endif
#ifdef _18F2455
    T2CON = (T2_NumPulses-2)<<3 | 0 | 0; // Num Pulses + T2Off + Prescale 1
#endif
    TMR2 = 0;               // TMR2 is 8-bits wide
    PIR1bits.TMR2IF = 0;    // Clear the interrupt flag
    PIE1bits.TMR2IE = 0;    // Disable Interrupts
    
}
