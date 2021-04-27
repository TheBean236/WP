
#include "Master.h"
#include "CommonRoutines.h"
#include "LCD.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

// Known Constants
#define gc_pi           3.1416926f
#define gc_SOS_at_0     331.3e3
#define gc_AbsZero      273.15   
#define gc_GalsPer_mm3  264.172052e-9 
#define gc_DefaultTemp  20.0
#define gc_TickPeriod   500.0e-9
#define gc_mmPerIn      25.4


// Tank Dimensions
#define gc_TankDiam_In      48
#define gc_SensorHeight_In    72
#define gc_MaxWaterHeight_In 72

double  gd_Temp;
double  gd_TankSurfArea_mm2;
double  gd_SensorHeight_mm;
double  gd_TankGalsPer_mm;
double  gd_MaxWaterHeight_mm;
double  gd_Default_SOS;

void InitTankVariables (void);
void ComputeWaterVol (void);

/* ---------------------------------------------------------------------
                         Main application
    --------------------------------------------------------------------*/

#define LowCalcs    1
#define FullCalcs   2
#define Calcs       FullCalcs
#define LCD         true

// LCD Display Buffers
uint8_t sLine1[100];        // LCD Display Line1
uint8_t sLine2[100];        // LCD Display Line2

// LCD Backlight and debounce variables
bool    gbBacklight_On      = false;
bool    giBacklight_Timeout = 1;
#define gbBacklight_Request PORTCbits.RC4

// Relay Control
#define gbRelayOn   PORTAbits.RA0

void SysInit       (void);
void ComputeTOD    (void);

void main(void)
{
    // Initialize the device
    SysInit();

    if (LCD)
    {
       LCD_Init();         // Initialize LCD Display
       LCD_WriteString ((uint8_t *)"Loading... ");  
    }
    
    // Amount to time to turn on the backlight when button is pressed (Seconds)
    giBacklight_Timeout = (PORTCbits.RC0) ? 180 : 2;
    
    InitTankVariables(); 
    Timer0_Init();      // Initialize and start TOD clock
    Timer1_Init();      // Initialize Timer 1 (Echo Timer)
    Timer2_Init();      // Initialize 40 Khz clock
    CCP1_Init();        // Initialize CCP1 - Echo counter
    CCP2_Init();        // Initialize 40 Khz PWM module
    
    INTCONbits.GIE = 1; // Enable Global Interrupts
    INTCONbits.PEIE = 1;  // Enable Peripheral Interrupts

    while (1)
    {
        if (gb_EchoDetected)
        {
            ComputeWaterVol();
            gb_EchoDetected = false;
        }
        if (gb_UpdateTime)      // TMR0 (1-second timer) fired.
        {
            ComputeTOD();
            gb_UpdateTime = false;
        }
        
        // See if we should turn on the LCD Backlight
        if (!gbBacklight_On)
        {
            if (gbBacklight_Request)        // > IF : Pin RC4 is high
            {
                LATAbits.LA4 = 1;           // >THEN: Turn on the LCD Backlight
                gbBacklight_On = true;
                giBacklight_Timer = 0;      // > AND: Initialize backlight on timer
            }
        } else {
            if (giBacklight_Timer > giBacklight_Timeout)
            { 
                if (!gbBacklight_Request)
                {
                    gbBacklight_On = false;
                    LATAbits.LATA4 = 0;
                }
            }     
        }
    }
}

void ComputeWaterVol()
{
    float dCurrTemp;
    float dSOS = gd_Default_SOS;
    float d_mmPerTick;
    float dEmptySpace_mm;
    float dWaterHeight_mm;
    float dWaterVol;
    float dEchoPeriod;
    uint16_t iPercentFull;
    uint16_t iGals;
    uint16_t iEmptySpace_mm;
    
    dEchoPeriod = giEchoCounter.EP16 * gc_TickPeriod;
    dCurrTemp  = gc_DefaultTemp;
    dSOS       = gc_SOS_at_0 * sqrt( 1 + (dCurrTemp / gc_AbsZero));
    d_mmPerTick = dSOS * gc_TickPeriod / 2;
    // The uSonic sensor has a 2.2ms delay before starting 
    // .. so we subtract 4400 from the counter
    dEmptySpace_mm  = (giEchoCounter.EP16 - 4400) * d_mmPerTick;
    iEmptySpace_mm = dEmptySpace_mm;

    //if (dEmptySpace_mm > 1810) __debug_break();
    if (Calcs == FullCalcs)     // > IF : Full Calculations
    {                           // >THEN: Determine water volume
        dWaterHeight_mm = gd_SensorHeight_mm - dEmptySpace_mm;
        dWaterVol      = dWaterHeight_mm * gd_TankGalsPer_mm;
        iPercentFull = dWaterHeight_mm * 100 / gd_MaxWaterHeight_mm;
        iGals = dWaterVol;      // Simple convert to integer
    } else {                    // >ELSE: Not calculating
        iPercentFull = 50;      // >THEN: load dummy variables for display
        iGals       = 100;
    }
        
    // See if we need to turn the relay on or off
    // NOTE:    false = 0
    //          true = 1

    if (LATAbits.LATA0 == 1)
    {
        if (iPercentFull < 20) LATAbits.LATA0 = 0;
    } else {
        if (iPercentFull > 70) LATAbits.LATA0 = 1;
    }
 
    if (LCD)
    {
        LCD_GoTo (0, 0);
        sprintf(sLine1, "Gals: %4.0u %3.1u%% ", iGals, iPercentFull);
        LCD_WriteString (sLine1);

        LCD_GoTo(1, 0);
        sprintf(sLine2, "Echo: %4.0u ", iEmptySpace_mm);
        LCD_WriteString (sLine2);
        Nop();                      // Allows setting a breakpoint
    }
}

void InitTankVariables (void)
{
    gd_TankSurfArea_mm2 = gc_pi * pow(gc_TankDiam_In * gc_mmPerIn / 2, 2);
    gd_SensorHeight_mm  = gc_SensorHeight_In * gc_mmPerIn;
    gd_TankGalsPer_mm   = gd_TankSurfArea_mm2 * gc_GalsPer_mm3;
    gd_MaxWaterHeight_mm = gc_MaxWaterHeight_In * gc_mmPerIn;
    gd_Default_SOS      = gc_SOS_at_0 * sqrt( 1 + (gc_DefaultTemp / gc_AbsZero));
}

void ComputeTOD()
{
    bool bIncDays = false;
    
    if (++giTotalSecs >= 999) giTotalSecs = 0;
    if (++giSecs >= 60)
    {
        giSecs = 0;
        if (++giMins >= 60) 
        {
            giMins = 0;
            if (++giHours >= 24){
                giHours = 0;
                bIncDays = true;
            }
        }
    }
    if (LCD)
    {
        sprintf(gsTotalSecs, "%3i", giTotalSecs);
        LCD_GoTo (1, 12);
        LCD_WriteString (gsTotalSecs);
    }
    
    // Check for Date Change
    if (bIncDays)
    {
        if (++giDay > giMonthEndTbl[giMonth - 1])
        {
            giDay = 1;
            if (++giMonth > 12)
            {
                giMonth = 1;
                giYear ++;
            }
        }
    }
}

/**
 End of File
*/