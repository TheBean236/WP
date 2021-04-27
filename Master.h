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


#define _XTAL_FREQ  8000000
#define S_Clock     8000000
#define I_Clock     2000000
// Timer 0 (Time-of-Day)
#define T0_Period   1
#define T0_LED_Toggle() do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LCD_BL_Toggle() do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
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

// Timer 1 (Echo Timer) is in uS
#define T1_Period   0.5f           
#define T1_mm_Per_Tick  .343f    

// Timer 2 (40Khz Oscillator) 
#define T2_Period       25
#define T2_IncRate      1
#define T2_NumPulses    10

// Timer 3 (Sample Timer) Period is in mSeconds
// e.g. 1 sample every 5 ms
#define T3_Prescale     8
#define T3_Period       5
#define T3_Freq         (1000 / T3_Period)
#define T3_SampeRate    10

// Sample Rate is in number of 5 ms increments (e.g. 10 = 1/2 second)
#define gcSampleRate    10

// Pin Definitions  (Write to latch, read from port)
#define Pin_Echo_Detect PORTCbits.CCP1
#define Pin_Tx_Enable   LATAbits.LATA5
#define Pin_Relay       LATAbits.LATA0
#define Pin_LCD_E       LATAbits.LATA1
#define Pin_LCD_RW      LATAbits.LATA2
#define Pin_LCD_RS      LATAbits.LATA3
#define Pin_LCD_BackLite LATAbits.LATA4

// Display Strings
volatile char gsCurrDate[] = "01/04/21";
volatile char gsCurrTime[] = "01:00:00";
volatile char gsTotalSecs[] = "---";

volatile bool gb_UpdateTime   = false;
volatile bool gb_EchoDetected = false;

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
// It's okay if it overflows. noone cares. 
uint16_t    giBacklight_Timer = 0;

// DEFINE MODE: Test or Normal
#define Test_Mode
//#Define Normal_Mode

#endif	/* Master_H */

