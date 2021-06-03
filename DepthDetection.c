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
#include "SWTimer.h"

// Local Vars - Computed in InitTankVariables
float  gfTankSurfArea_mm2;
float  gfSensorHeight_mm;
float  gfTankGalsPer_mm;
float  gfMaxWaterHeight_mm;
float  gfDefault_SOS;

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
    SWTimer_Start();
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
    dWaterHeight_mm = gfSensorHeight_mm - dEmptySpace_mm;
    dWaterVol      = dWaterHeight_mm * gfTankGalsPer_mm;
    giPercentFull = dWaterHeight_mm * 100 / gfMaxWaterHeight_mm;
    giGals = round(dWaterVol);      // Simple convert to integer
    
    // See if we need to turn the relay on or off
    // NOTE:    false = 0
    //          true = 1
    if (Pin_Relay == 1) {
        if (giPercentFull < gcRelayOffPercent) Pin_Relay = 0;
    } else {
        if (giPercentFull > gcRelayOnPercent) Pin_Relay = 1;
    }
 
    if (LCD) LCD_DisplayResults();
    SWTimer_Stop();
    SWTimer_Read();
    Nop();
}
    
    void InitTankVariables (void)
{
    if (gcTankType == gcTankCylinder)   // > IF: It's a Cylinder
        gfTankSurfArea_mm2 = gc_pi * pow(gcTankDiameter * gc_mmPerIn / 2, 2);
    else                                // ELSE: It's a rectange
        gfTankSurfArea_mm2 =    (gcTankWidth * gc_mmPerIn) * 
                                (gcTankLength * gc_mmPerIn);
    gfSensorHeight_mm  = gcSensorHeight * gc_mmPerIn;
    gfTankGalsPer_mm   = gfTankSurfArea_mm2 * gc_GalsPer_mm3;
    gfMaxWaterHeight_mm = gcMaxWaterHeight * gc_mmPerIn;
    gfDefault_SOS      = gc_SOS_at_0 * sqrt( 1 + (gc_DefaultTemp / gc_AbsZero));
}
