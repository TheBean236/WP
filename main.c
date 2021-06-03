
#include "Master.h"
#include "CommonRoutines.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

double  gd_Temp;

void InitTankVariables (void);
void ComputeWaterVol (void);

/* ---------------------------------------------------------------------
                         Main application
    --------------------------------------------------------------------*/
// LCD Backlight variables
bool    gbBacklight_On      = false;
uint8_t    giBacklight_Timeout = 5;

void SysInit        (void);
void ComputeTOD     (void);

void main(void)
{
    // Initialize the device
    SysInit();

    if (LCD)
    {
       LCD_Init();         // Initialize LCD Display
       LCD_WriteString ((uint8_t *)"Loading... ");  
    }

    Nop();
    // Amount to time to turn on the backlight when button is pressed (Seconds)
    giBacklight_Timeout = (Pin_3Min_Opt == 1) ? 180 : 10;
    
    InitTankVariables(); 
    Timer0_Init();      // Initialize and start TOD clock
    Timer1_Init();      // Initialize Timer 1 (Echo Timer)
    Timer2_Init();      // Initialize 40 Khz clock
    Timer3_Init();      // Software timers
    CCP1_Init();        // Initialize CCP1 - Echo counter
    CCP2_Init();        // Initialize 40 Khz PWM module
    AN0_Init();         // Initialize Thermistor A/D Converter
    
    INTCONbits.GIE = 1; // Enable Global Interrupts
    INTCONbits.PEIE = 1;  // Enable Peripheral Interrupts

    /* ------------------------------   Main  --------------------------
     *  Process:
     *      The Interrupt modules set flags for background processing
     *      Time-of-Day:    gb_UpdateTime   Interrupts 1/sec. 
     *      A/D:            gb_Temp_Captured    Interrupts on completion of A/D
     *                                          Starts Temp Calculations
     *      Temp:           gb_Temp_Done        When Temp Calculation Done
     *                                          Starts Echo Detect
     *      Echo:           gb_EchoDetected     Interrupts when Echo Detected
     *      Backlight:      Poll Backlight BIt  Turn on/off backlight
     *----------------------------------------------------------------*/
    while (1)
    {
        if (gb_TempCaptured)   // A/D Conversion complete on Temp A/D
        {
            gb_TempCaptured = false;
            ComputeTemp();
            StartDepthDetection();
        }
        
        if (gb_EchoDetected)
        {
            ComputeWaterVol();
            gb_EchoDetected = false;
        }
        
        if (gb_UpdateTime)      // TOD Update: TMR0 (1-second timer) fired.
        {
            ComputeTOD();
            gb_UpdateTime = false;
            
            // See if we should turn on the LCD Backlight
            if (!gbBacklight_On)
            {
                if (Pin_BkLite_Req == 1)        // > IF : Pin RC4 is high
                {
                    Pin_LCD_BackLite = 1;       // >THEN: Turn on the LCD Backlight
                    gbBacklight_On = true;
                    giBacklight_Timer = 0;      // > AND: Initialize backlight on timer
                }
            } else {
                if (++giBacklight_Timer > giBacklight_Timeout)
                { 
                    if (Pin_BkLite_Req == 0)
                    {
                        gbBacklight_On = false;
                        Pin_LCD_BackLite = 0;
                    }
                }     
            }
        }
    }
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
        //LCD_WriteString (gsTotalSecs);
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