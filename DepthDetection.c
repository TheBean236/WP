/*
 * File:   DepthDetection
 * Author: MBender
 *
 * This routine controls and calculates the air temperature in the
 * container 
 */
#include <math.h>
#include "Master.h"
#include "CommonRoutines.h"

// Local Vars - Computed in InitTankVariables
double  gd_TankSurfArea_mm2;
double  gd_SensorHeight_mm;
double  gd_TankGalsPer_mm;
double  gd_MaxWaterHeight_mm;
double  gd_Default_SOS;

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
    Pin_Tx_Enable       = 0;    // Fire the digital transmitter
    T1CONbits.TMR1ON    = 1;    // Start TMR1
}

void ComputeWaterVol()
{
    float dCurrTemp;
    float d_mmPerTick;
    float dEmptySpace_mm;
    float dWaterHeight_mm;
    float dWaterVol;
    float dEchoPeriod;
    float dSOS;
    
    dEchoPeriod = giEchoCounter.EP16 * gc_TickPeriod;
    dCurrTemp  = gfAirTempC;
    dSOS       = gc_SOS_at_0 * sqrt( 1 + (dCurrTemp / gc_AbsZero));
    d_mmPerTick = dSOS * gc_TickPeriod / 2;
    
    // The Digital uSonic sensor has a 2.2ms delay before starting 
    // .. so we subtract 4400 from the counter
    if (SensorType == DigitalSensor)
        dEmptySpace_mm = (giEchoCounter.EP16 - 4400) * d_mmPerTick;
    else
        dEmptySpace_mm = giEchoCounter.EP16 * d_mmPerTick;
    giEmptySpace_mm = dEmptySpace_mm;
    dWaterHeight_mm = gd_SensorHeight_mm - dEmptySpace_mm;
    dWaterVol      = dWaterHeight_mm * gd_TankGalsPer_mm;
    giPercentFull = dWaterHeight_mm * 100 / gd_MaxWaterHeight_mm;
    giGals = round(dWaterVol);      // Simple convert to integer
    
    // See if we need to turn the relay on or off
    // NOTE:    false = 0
    //          true = 1
    if (Pin_Relay == 1) {
        if (giPercentFull < gc_RelayOffPercent) Pin_Relay = 0;
    } else {
        if (giPercentFull > gc_RelayOnPercent) Pin_Relay = 1;
    }
 
    if (LCD) LCD_DisplayResults();
}
    
    void InitTankVariables (void)
{
    gd_TankSurfArea_mm2 = gc_pi * pow(gc_TankDiam_In * gc_mmPerIn / 2, 2);
    gd_SensorHeight_mm  = gc_SensorHeight_In * gc_mmPerIn;
    gd_TankGalsPer_mm   = gd_TankSurfArea_mm2 * gc_GalsPer_mm3;
    gd_MaxWaterHeight_mm = gc_MaxWaterHeight_In * gc_mmPerIn;
    gd_Default_SOS      = gc_SOS_at_0 * sqrt( 1 + (gc_DefaultTemp / gc_AbsZero));
}
