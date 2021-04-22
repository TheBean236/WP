/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F45K50
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set Relay aliases
#define Relay_TRIS                 TRISAbits.TRISA0
#define Relay_LAT                  LATAbits.LATA0
#define Relay_PORT                 PORTAbits.RA0
#define Relay_ANS                  ANSELAbits.ANSA0
#define Relay_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define Relay_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define Relay_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define Relay_GetValue()           PORTAbits.RA0
#define Relay_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define Relay_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define Relay_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define Relay_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set LCD_E aliases
#define LCD_E_TRIS                 TRISAbits.TRISA1
#define LCD_E_LAT                  LATAbits.LATA1
#define LCD_E_PORT                 PORTAbits.RA1
#define LCD_E_ANS                  ANSELAbits.ANSA1
#define LCD_E_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LCD_E_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LCD_E_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LCD_E_GetValue()           PORTAbits.RA1
#define LCD_E_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LCD_E_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LCD_E_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define LCD_E_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set LCD_RW aliases
#define LCD_RW_TRIS                 TRISAbits.TRISA2
#define LCD_RW_LAT                  LATAbits.LATA2
#define LCD_RW_PORT                 PORTAbits.RA2
#define LCD_RW_ANS                  ANSELAbits.ANSA2
#define LCD_RW_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LCD_RW_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LCD_RW_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LCD_RW_GetValue()           PORTAbits.RA2
#define LCD_RW_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LCD_RW_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LCD_RW_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LCD_RW_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set LCD_RS aliases
#define LCD_RS_TRIS                 TRISAbits.TRISA3
#define LCD_RS_LAT                  LATAbits.LATA3
#define LCD_RS_PORT                 PORTAbits.RA3
#define LCD_RS_ANS                  ANSELAbits.ANSA3
#define LCD_RS_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define LCD_RS_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define LCD_RS_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define LCD_RS_GetValue()           PORTAbits.RA3
#define LCD_RS_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define LCD_RS_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define LCD_RS_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define LCD_RS_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set Tx_Enable aliases
#define Tx_Enable_TRIS                 TRISAbits.TRISA5
#define Tx_Enable_LAT                  LATAbits.LATA5
#define Tx_Enable_PORT                 PORTAbits.RA5
#define Tx_Enable_ANS                  ANSELAbits.ANSA5
#define Tx_Enable_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define Tx_Enable_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define Tx_Enable_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define Tx_Enable_GetValue()           PORTAbits.RA5
#define Tx_Enable_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define Tx_Enable_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define Tx_Enable_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define Tx_Enable_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set IO_RB0 aliases
#define IO_RB0_TRIS                 TRISBbits.TRISB0
#define IO_RB0_LAT                  LATBbits.LATB0
#define IO_RB0_PORT                 PORTBbits.RB0
#define IO_RB0_WPU                  WPUBbits.WPUB0
#define IO_RB0_ANS                  ANSELBbits.ANSB0
#define IO_RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define IO_RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define IO_RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define IO_RB0_GetValue()           PORTBbits.RB0
#define IO_RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define IO_RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define IO_RB0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define IO_RB0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define IO_RB0_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define IO_RB0_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set IO_RB1 aliases
#define IO_RB1_TRIS                 TRISBbits.TRISB1
#define IO_RB1_LAT                  LATBbits.LATB1
#define IO_RB1_PORT                 PORTBbits.RB1
#define IO_RB1_WPU                  WPUBbits.WPUB1
#define IO_RB1_ANS                  ANSELBbits.ANSB1
#define IO_RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define IO_RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define IO_RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define IO_RB1_GetValue()           PORTBbits.RB1
#define IO_RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define IO_RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define IO_RB1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define IO_RB1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define IO_RB1_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define IO_RB1_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set IO_RB2 aliases
#define IO_RB2_TRIS                 TRISBbits.TRISB2
#define IO_RB2_LAT                  LATBbits.LATB2
#define IO_RB2_PORT                 PORTBbits.RB2
#define IO_RB2_WPU                  WPUBbits.WPUB2
#define IO_RB2_ANS                  ANSELBbits.ANSB2
#define IO_RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define IO_RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define IO_RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define IO_RB2_GetValue()           PORTBbits.RB2
#define IO_RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define IO_RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define IO_RB2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define IO_RB2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define IO_RB2_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define IO_RB2_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set IO_RB3 aliases
#define IO_RB3_TRIS                 TRISBbits.TRISB3
#define IO_RB3_LAT                  LATBbits.LATB3
#define IO_RB3_PORT                 PORTBbits.RB3
#define IO_RB3_WPU                  WPUBbits.WPUB3
#define IO_RB3_ANS                  ANSELBbits.ANSB3
#define IO_RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define IO_RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define IO_RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define IO_RB3_GetValue()           PORTBbits.RB3
#define IO_RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define IO_RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define IO_RB3_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define IO_RB3_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define IO_RB3_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define IO_RB3_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set IO_RB4 aliases
#define IO_RB4_TRIS                 TRISBbits.TRISB4
#define IO_RB4_LAT                  LATBbits.LATB4
#define IO_RB4_PORT                 PORTBbits.RB4
#define IO_RB4_WPU                  WPUBbits.WPUB4
#define IO_RB4_ANS                  ANSELBbits.ANSB4
#define IO_RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_RB4_GetValue()           PORTBbits.RB4
#define IO_RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_RB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_RB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_RB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_RB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set IO_RB5 aliases
#define IO_RB5_TRIS                 TRISBbits.TRISB5
#define IO_RB5_LAT                  LATBbits.LATB5
#define IO_RB5_PORT                 PORTBbits.RB5
#define IO_RB5_WPU                  WPUBbits.WPUB5
#define IO_RB5_ANS                  ANSELBbits.ANSB5
#define IO_RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IO_RB5_GetValue()           PORTBbits.RB5
#define IO_RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IO_RB5_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IO_RB5_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IO_RB5_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define IO_RB5_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set IO_RB6 aliases
#define IO_RB6_TRIS                 TRISBbits.TRISB6
#define IO_RB6_LAT                  LATBbits.LATB6
#define IO_RB6_PORT                 PORTBbits.RB6
#define IO_RB6_WPU                  WPUBbits.WPUB6
#define IO_RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IO_RB6_GetValue()           PORTBbits.RB6
#define IO_RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define IO_RB6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IO_RB6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)

// get/set IO_RB7 aliases
#define IO_RB7_TRIS                 TRISBbits.TRISB7
#define IO_RB7_LAT                  LATBbits.LATB7
#define IO_RB7_PORT                 PORTBbits.RB7
#define IO_RB7_WPU                  WPUBbits.WPUB7
#define IO_RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define IO_RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define IO_RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define IO_RB7_GetValue()           PORTBbits.RB7
#define IO_RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define IO_RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define IO_RB7_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define IO_RB7_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)

// get/set Echo_Detect aliases
#define Echo_Detect_TRIS                 TRISCbits.TRISC2
#define Echo_Detect_LAT                  LATCbits.LATC2
#define Echo_Detect_PORT                 PORTCbits.RC2
#define Echo_Detect_ANS                  ANSELCbits.ANSC2
#define Echo_Detect_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define Echo_Detect_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define Echo_Detect_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define Echo_Detect_GetValue()           PORTCbits.RC2
#define Echo_Detect_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define Echo_Detect_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define Echo_Detect_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define Echo_Detect_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/