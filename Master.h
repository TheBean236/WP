/* 
 * File:        Master.h
 * Author:      MBB
 * Comments:    System master include file
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Master_H
#define	Master_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#ifdef _18F45K50
#define NumPins     40
#endif
#ifdef _18F2455
#define NumPins     28
#endif

/* -----------------------  Run Parameters  ---------------------------*/
#define _XTAL_FREQ  8000000
#define S_Clock     8000000
#define I_Clock     2000000
#define Vcc         5.075
#define LCD         true
// uSonic Sensor Type
#define DigitalSensor   0
#define AnalogSensor    1
#define SensorType      DigitalSensor
// LCD Interface
#define LCD_BusSize     8

// Sample Rate is in number of 5 ms increments (e.g. 100 = 1/2 second)
// Min Sample Rate = 10 (50 ms)
//  Water Depth Calc    = 20ms (including LCD Write)
//  Temp Calc           = 15ms
#define gcSampleRate    10

// ------------------------- Known Constants ----------------------------
#define gc_pi           3.1416926
#define gc_SOS_at_0     331.3e3
#define gc_AbsZero      273.15   
#define gc_GalsPer_mm3  264.172052e-9 
#define gc_TickPeriod   500.0e-9
#define gc_mmPerIn      25.4

// Default Temp = 72 Deg F = 22.22 Deg C
#define gc_DefaultTemp  22.22

// A/D Resistor Calculation Macros
#define RsOnTop(R2, ADmax, AD)     ((R2 * (ADmax - AD)) / AD)
#define RsOnBottom(R1, ADmax, AD)  ((R1 * AD) / (ADmax - AD))

/* ------------------------ Tank Dimensions ---------------------------
 * NOTE: All tank dimensions are in Inches
 *       Initialization routine will convert to mm
 * --------------------------------------------------------------------- */
#define gcTankCylinder          0
#define gcTankRectangle         1
#define gcTankType              gcTankRectangle
#define gcTankDiameter          48.
#define gcSensorHeight          72.
#define gcTankWidth             12.125
#define gcTankLength            15.5
#define gcMaxWaterHeight        8.0
#define gcRelayOnPercent        80
#define gcRelayOffPercent       25

// gi_SW_Time is used to compute module execution times
uint16_t gi_SW_Time;        // SW Timer - Number of instructions executed

typedef union EchoPeriod_tag
{
   struct
   {
      uint8_t EPl;
      uint8_t EPh;
   };
   struct
   {
      uint16_t EP16;
   };
} EchoPeriod_t;
volatile EchoPeriod_t giEchoCounter;

// ------------------------  Timer Setup  --------------------------
// Timer 0 (Time-of-Day & Sample Timer)
#define T3_Period       5
#define T0_Freq         (1000 / T0_Period)

// Timer 1 (Echo Timer) is in uS
#define T1_Period       0.5f           
 
// Timer 2 (40Khz Oscillator) 
#define T2_Period       25
#define T2_IncRate      1
#define T2_NumPulses    10

// Timer 3 (Sample Timer) Period is in mSeconds
// Used for module execution timings only

// --------------------  Port A Pin Definitions  ---------------------
// RA0 - Thermistor A/D
#define Pin_Therm_TRIS  TRISAbits.RA0
#define Pin_Therm_LAT   LATAbits.LATA0

// RA1 - LCD_E
#define Pin_LCD_E       LATAbits.LATA1
#define Pin_LCD_E_LAT   LATAbits.LATA1
#define Pin_LCD_E_TRIS  TRISAbits.RA1

// RA2 - LCD_RW
#define Pin_LCD_RW      LATAbits.LATA2
#define Pin_LCD_RW_LAT  LATAbits.LATA2
#define Pin_LCD_RW_TRIS TRISAbits.RA2

// RA3 - LCD-RW
#define Pin_LCD_RS      LATAbits.LATA3
#define Pin_LCD_RS_LAT  LATAbits.LATA3
#define Pin_LCD_RS_TRIS TRISAbits.RA3

// RA4 - LCD Backlight
#define Pin_LCD_BackLite        LATAbits.LATA4
#define Pin_LCD_BackLite_LAT    LATAbits.LATA4
#define Pin_LCD_BackLite_TRIS   TRISAbits.RA4

// RA5 - Tx-Enable
#define Pin_Tx_Enable           LATAbits.LATA5
#define Pin_Tx_Enable_LAT       LATAbits.LATA5
#define Pin_Tx_Enable_TRIS      TRISAbits.TRISA5

// RA6 - RA7 = Oscillator

// -------------------  Port B Pin Definitions  ----------------------
//  All port B pins are outputs (LCD Data))

// -------------------- Port C Pin Definitions  ----------------------
// RC0 - Relay Driver
#define Pin_Relay       LATCbits.LATC0
#define Pin_Relay_LAT   LATCbits.LATC0
#define Pin_Relay_TRIS  TRISCbits.RC0

// RC1 - 40Khz Out
#define Pin_40Khz_TRIS   TRISCbits.RC1

// RC2 - Echo Detect
#define Pin_Echo_Detect         PORTCbits.RC2
#define Pin_Echo_Detect_LAT     LATCbits.LATC2
#define Pin_Echo_Detect_TRIS    TRISCbits.RC2

// RC3 - USB Vout

// RC4 - Backlight Request
#define Pin_BkLite_Req          PORTCbits.RC4
    // RC4 has no LAT
    // RC4 has no TRIS - Input only

// RC5 - 3-min backlight option
#define Pin_3Min_Opt            PORTCbits.RC5
    // RC5 has no LAT
    // RC5 has no TRIS - Input Only

// RC6 - LCD Data 6
#define Pin_LCD_Data6       LATCbits.LATC6
#define Pin_LCD_Data6_LAT   LATCbits.LATC6
#define Pin_LCD_Data6_TRIS  TRISCbits.RC6

// RC7 - LCD Data 7
#define Pin_LCD_Data7       LATCbits.LATC7
#define Pin_LCD_Data7_LAT   LATCbits.LATC7
#define Pin_LCD_Data7_TRIS  TRISCbits.RC7

// Display Strings
volatile char gsCurrDate[] = "01/04/21";
volatile char gsCurrTime[] = "01:00:00";
volatile char gsTotalSecs[] = "---";

// Even Process Flags
volatile bool gb_UpdateTime     = false;
volatile bool gb_EchoDetected   = false;
volatile bool gb_Temp_Captured  = false;
volatile bool gb_Temp_Done      = false;

// Thermistor Globals (Air Temp)
volatile bool gb_TempCaptured  = false;
volatile uint16_t giTempCapture;    // Digital capture to temp A/D Converter
volatile float gfAirTempC;          // Floating point Deg C
volatile int giAirTempC;            // in Degrees C
volatile int giAirTempF;            // in Degrees F

// Water Vol Globals
volatile uint16_t giGals;           // Gallons of water
volatile uint16_t giPercentFull;    // Percent Full
volatile uint16_t giEmptySpace_mm;  // Empty Space Above Water Level

// LCD Display Buffers
uint8_t sLine1[100];        // LCD Display Line1
uint8_t sLine2[100];        // LCD Display Line2

// Time of Day and Date Vars
// Month End Table         J  F  M  A  M  Jn Jl A  S  O  N  D
uint8_t giMonthEndTbl[] = {31,28,31,30,31,30,31,31,30,31,30,31};
uint16_t giTotalSecs = 0;
uint8_t giSecs   = 0;
uint8_t giMins   = 0;
uint8_t giHours  = 0;
uint8_t giDay   = 1;
uint8_t giMonth = 4;
uint8_t giYear  = 21;

// biBacklightTimer increments every second from TMR0. 
// the main routine clears the counter upon detection of 
// a push-button request to turn on the LCD backlight. 
// Main also checks the counter for when to turn off
// the backlight.
// It's okay if it overflows. no one cares. 
uint16_t    giBacklight_Timer = 0;

#endif	/* Master_H */

