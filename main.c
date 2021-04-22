
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
#define gc_MaxWaterHeight_In 68

double  gd_Temp;
double  gd_TankSurfArea_mm2;
double  gd_SensorHeight_mm;
double  gd_TankGalsPer_mm;
double  gd_MaxWaterHeight_mm;

void InitTankVariables (void);
void ComputeWaterVol (void);

/*
                         Main application
 */


uint8_t LCD_TestString1[] = {"ABCDEFIJKLMNOPQRS"};
uint8_t LCD_TestString2[] = {"1234567890123456"};
uint8_t LCD_TestString3[] = {0x80, 0x81, 0x82, 0x83, 0x84};

#define LCD true

void SysInit        (void);
void ComputeTOD    (void);

void main(void)
{
    uint8_t iLine = 0;
    
    // Initialize the device
    SysInit();

    if (LCD)
    {
       LCD_Init();         // Initialize LCD Display
       LCD_WriteString ("Gals:---- ---%");
       LCD_GoTo(1, 0);
       LCD_WriteString ("Echo:----mm ---S");  
    }
    
    InitTankVariables(); 
    Timer0_Init();      // Initialize and start TOD clock
    Timer1_Init();      // Initialize Timer 1 (Echo Timer)
    Timer2_Init();      // Initialize 40 Khz clock
    Timer3_Init();      // Initialize and Start Sample clock
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
        if (gb_UpdateTime)
        {
            ComputeTOD();
            gb_UpdateTime = false;
        }
    }
}

void ComputeWaterVol()
{
    float d_CurrTemp;
    float d_SOS;
    float d_mmPerTick;
    float d_EmptySpace_mm;
    float d_WaterHeight_mm;
    float d_WaterVol;
    float d_EchoPeriod;
    uint8_t i_PercentFull;
    uint16_t i_Gals;
    uint8_t sGals[] = "----          ";
    uint8_t sFill[] = "---          ";
    uint8_t sEchoMM[] = "xxxx      ";

    d_EchoPeriod = giEchoCounter.EP16 * gc_TickPeriod;
    d_CurrTemp  = gc_DefaultTemp;
    d_SOS       = gc_SOS_at_0 * sqrt( 1 + (d_CurrTemp / gc_AbsZero));
    d_mmPerTick = d_SOS * gc_TickPeriod / 2;
    d_EmptySpace_mm  = (giEchoCounter.EP16 - 4400) * d_mmPerTick;
    d_WaterHeight_mm = gd_SensorHeight_mm - d_EmptySpace_mm;
    d_WaterVol      = d_WaterHeight_mm * gd_TankGalsPer_mm;
    i_PercentFull = d_WaterHeight_mm * 100 / gd_MaxWaterHeight_mm;
    i_Gals = d_WaterVol;
    
    // Write results to the display
    sprintf(sGals, "%4i", i_Gals);
    LCD_GoTo (0, 5);    
    LCD_WriteString (sGals);

    sprintf (sFill, "%3i", i_PercentFull);
    LCD_GoTo (0, 10);
    LCD_WriteString (sFill);
    
    sprintf( sEchoMM, "%4.0f", d_EmptySpace_mm);
    LCD_GoTo (1,5);
    LCD_WriteString (sEchoMM);
}

void InitTankVariables (void)
{
    gd_TankSurfArea_mm2 = gc_pi * pow(gc_TankDiam_In * gc_mmPerIn / 2, 2);
    gd_SensorHeight_mm  = gc_SensorHeight_In * gc_mmPerIn;
    gd_TankGalsPer_mm   = gd_TankSurfArea_mm2 * gc_GalsPer_mm3;
    gd_MaxWaterHeight_mm = gc_MaxWaterHeight_In * gc_mmPerIn;
}

void ComputeTOD()
{
    bool bIncDays = false;
    
    if (giTotalSecs++ >= 999) giTotalSecs = 0;
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
    sprintf(gsTotalSecs, "%3i", giTotalSecs);
    LCD_GoTo (1, 12);
    LCD_WriteString (gsTotalSecs);
    //sprintf(gsCurrTime, "%i2/%i2/%i2", giHours, giMins, giSecs);
    
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
        //sprintf (gsCurrDate, "&n2/%n2/%n2", giMonth, giDay, giYear);
    }
}

/**
 End of File
*/