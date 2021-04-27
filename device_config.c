/**
  @Generated PIC10 / PIC12 / PIC16 / PIC18 MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the device_config.c file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F45K50
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above or later
        MPLAB             :  MPLAB X 5.45
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

// Configuration bits: selected in the GUI

#ifdef _18F45K50
// CONFIG1L
#pragma config PLLSEL = PLL4X    // PLL Selection->4x clock multiplier
#pragma config CFGPLLEN = OFF    // PLL Enable Configuration bit->PLL Disabled (firmware controlled)
#pragma config CPUDIV = NOCLKDIV    // CPU System Clock Postscaler->CPU uses system clock (no divide)
#pragma config LS48MHZ = SYS24X4    // Low Speed USB mode with 48 MHz system clock->System clock at 24 MHz, USB clock divider is set to 4

// CONFIG1H
#pragma config FOSC = HSM    // Oscillator Selection->HS oscillator, medium power 4MHz to 16MHz
#pragma config PCLKEN = ON    // Primary Oscillator Shutdown->Primary oscillator enabled
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor->Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF    // Internal/External Oscillator Switchover->Oscillator Switchover mode disabled

// CONFIG2L
#pragma config nPWRTEN = OFF    // Power-up Timer Enable->Power up timer disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable->BOR enabled in hardware (SBOREN is ignored)
#pragma config BORV = 190    // Brown-out Reset Voltage->BOR set to 1.9V nominal
#pragma config nLPBOR = OFF    // Low-Power Brown-out Reset->Low-Power Brown-out Reset disabled

// CONFIG2H
#pragma config WDTEN = OFF    // Watchdog Timer Enable bits->WDT disabled in hardware (SWDTEN ignored)
#pragma config WDTPS = 32768    // Watchdog Timer Postscaler->1:32768

// CONFIG3H
#pragma config CCP2MX = RC1    // CCP2 MUX bit->CCP2 input/output is multiplexed with RC1
#pragma config PBADEN = OFF    // PORTB A/D Enable bit->PORTB<5:0> pins are configured as analog input channels on Reset
#pragma config T3CMX = RC0    // Timer3 Clock Input MUX bit->T3CKI function is on RC0
#pragma config SDOMX = RB3    // SDO Output MUX bit->SDO function is on RB3
#pragma config MCLRE = ON    // Master Clear Reset Pin Enable->MCLR pin enabled; RE3 input disabled

// CONFIG4L
#pragma config STVREN = ON    // Stack Full/Underflow Reset->Stack full/underflow will cause Reset
#pragma config LVP = ON    // Single-Supply ICSP Enable bit->Single-Supply ICSP enabled if MCLRE is also 1
#pragma config ICPRT = OFF    // Dedicated In-Circuit Debug/Programming Port Enable->ICPORT disabled
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Instruction set extension and Indexed Addressing mode disabled
#pragma config DEBUG = OFF    // Background Debugger Enable bit->Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins

// CONFIG5L
#pragma config CP0 = OFF    // Block 0 Code Protect->Block 0 is not code-protected
#pragma config CP1 = OFF    // Block 1 Code Protect->Block 1 is not code-protected
#pragma config CP2 = OFF    // Block 2 Code Protect->Block 2 is not code-protected
#pragma config CP3 = OFF    // Block 3 Code Protect->Block 3 is not code-protected

// CONFIG5H
#pragma config CPB = OFF    // Boot Block Code Protect->Boot block is not code-protected
#pragma config CPD = OFF    // Data EEPROM Code Protect->Data EEPROM is not code-protected

// CONFIG6L
#pragma config WRT0 = OFF    // Block 0 Write Protect->Block 0 (0800-1FFFh) is not write-protected
#pragma config WRT1 = OFF    // Block 1 Write Protect->Block 1 (2000-3FFFh) is not write-protected
#pragma config WRT2 = OFF    // Block 2 Write Protect->Block 2 (04000-5FFFh) is not write-protected
#pragma config WRT3 = OFF    // Block 3 Write Protect->Block 3 (06000-7FFFh) is not write-protected

// CONFIG6H
#pragma config WRTC = OFF    // Configuration Registers Write Protect->Configuration registers (300000-3000FFh) are not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protect->Boot block (0000-7FFh) is not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protect->Data EEPROM is not write-protected

// CONFIG7L
#pragma config EBTR0 = OFF    // Block 0 Table Read Protect->Block 0 is not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF    // Block 1 Table Read Protect->Block 1 is not protected from table reads executed in other blocks
#pragma config EBTR2 = OFF    // Block 2 Table Read Protect->Block 2 is not protected from table reads executed in other blocks
#pragma config EBTR3 = OFF    // Block 3 Table Read Protect->Block 3 is not protected from table reads executed in other blocks

// CONFIG7H
#pragma config EBTRB = OFF    // Boot Block Table Read Protect->Boot block is not protected from table reads executed in other blocks
#endif

#ifdef _18F2455
/*  ----------------------------  Configuration Bits  --------------------------
 *  Configuration registers are defined in the 2455 DataSheet. Pages are listed
 *  These are sequensed based on Pragma description HTML file in 2455 directory 
 *  ----------------------------------------------------------------------------*/

// CONFIG1L     See page 283
// Set for 8Mhz Crystal. PLL Requires 4Mhz, so divide by 2
#pragma config PLLDIV   = 2     // PLL Input (must be 4Mhz) divide from Xtal
#pragma config CPUDIV   = OSC1_PLL2  // Not used with HS Oscillator
#pragma config USBDIV   = 2     // USB from PLL / 2

// CONFIG1H     See page 284
#pragma config FOSC     = HS    // High-Speed Crystal, PLL Disabled
#pragma config FCMEN    = OFF   // Fail-Safe Clock Monitor Enable Bit
#pragma config IESO     = OFF   // Internal/External Osc Switchover

// CONFIG2L     See page 285
#pragma config PWRT     = OFF   // Power-up Timer Enable Bit (negative)
#pragma config BOR      = OFF   // Disabled in Hardware
#pragma config BORV     = 2     // Brown-Out Reset Voltage 2.79v
#pragma config VREGEN   = OFF   // Internal VOltage Regulator Enable Bit

// CONFIG2H     See page 286
#pragma config WDT      = OFF   // Watchdog Timer Enable bits->WDT disabled in hardware (SWDTEN ignored)
#pragma config WDTPS    = 32768 // Watchdog Timer Postscaler->1:32768

// CONFIG3H     See page 287
#pragma config CCP2MX   = ON    // CCP2 MUX bit->CCP2 OFF = RB3, ON = RC1
#pragma config PBADEN   = OFF   // PORTB A/D Enable. Sets B<4:0> as analog on Reset
#pragma config LPT1OSC  = OFF   // Timer1 configured: ON = low-power operation, OFF = high-power
#pragma config MCLRE    = ON    // Master Clear Reset Pin Enable->MCLR pin enabled; RE3 input disabled

// CONFIG4L     See page 288
#pragma config STVREN   = ON    // Stack Full/Underflow Reset->Stack full/underflow will cause Reset
#pragma config LVP      = OFF   // Single-Supply ICSP Enable bit->Single-Supply ICSP enabled if MCLRE is also 1
#pragma config XINST    = OFF   // Extended Instruction Set Enable bit->Instruction set extension and Indexed Addressing mode disabled
#pragma config DEBUG    = OFF   // Background Debugger Enable bit->Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins

// CONFIG5L     See page 289
#pragma config CP0      = OFF    // Block 0 Code Protect->Block 0 is not code-protected
#pragma config CP1      = OFF    // Block 1 Code Protect->Block 1 is not code-protected
#pragma config CP2      = OFF    // Block 2 Code Protect->Block 2 is not code-protected

// CONFIG5H     See page 289
#pragma config CPB      = OFF    // Boot Block Code Protect->Boot block is not code-protected
#pragma config CPD      = OFF    // Data EEPROM Code Protect->Data EEPROM is not code-protected

// CONFIG6L     See page 288
#pragma config WRT0     = OFF    // Block 0 Write Protect->Block 0 (0800-1FFFh) is not write-protected
#pragma config WRT1     = OFF    // Block 1 Write Protect->Block 1 (2000-3FFFh) is not write-protected
#pragma config WRT2     = OFF    // Block 2 Write Protect->Block 2 (04000-5FFFh) is not write-protected

// CONFIG6H     See page 288
#pragma config WRTC     = OFF    // Configuration Registers Write Protect->Configuration registers (300000-3000FFh) are not write-protected
#pragma config WRTB     = OFF    // Boot Block Write Protect->Boot block (0000-7FFh) is not write-protected
#pragma config WRTD     = OFF    // Data EEPROM Write Protect->Data EEPROM is not write-protected

// CONFIG7L     See page 289
#pragma config EBTR0    = OFF    // Block 0 Table Read Protect->Block 0 is not protected from table reads executed in other blocks
#pragma config EBTR1    = OFF    // Block 1 Table Read Protect->Block 1 is not protected from table reads executed in other blocks
#pragma config EBTR2    = OFF    // Block 2 Table Read Protect->Block 2 is not protected from table reads executed in other blocks

// CONFIG7H
#pragma config EBTRB    = OFF    // Boot Block Table Read Protect->Boot block is not protected from table reads executed in other blocks
#endif
