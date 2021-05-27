/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F45K50
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB             :  MPLAB X 5.45
*/
#include "pin_manager.h"
#include "Master.h"

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
#ifdef _18F45K50
    LATE = 0x00;
    LATD = 0x00;
#endif
    LATA = 0x00;        // Initialize all outputs to Zero
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
#ifdef _18F45K50
    TRISE = 0x07;
    TRISD = 0xFF;
#endif
    // Pre-initialize all pins as inputs
    TRISA = 0xff;   // RA1 = Input (A/D)  Rest are outputs
    TRISB = 0xff;
    TRISC = 0xff;   // RC 2-5 are inputs. Rest are outputs

    // Set up Output Pins
    TRISB                   = 0;
    Pin_LCD_E_TRIS          = 0;
    Pin_LCD_RS_TRIS         = 0;
    Pin_LCD_RW_TRIS         = 0;
    Pin_LCD_BackLite_TRIS   = 0;
    Pin_Tx_Enable_TRIS      = 0;
    Pin_Relay_TRIS          = 0;
    Pin_40Khz_TRIS          = 0;
    Pin_LCD_Data6_TRIS      = 0;
    Pin_LCD_Data7_TRIS      = 0;
    
    /*---------------------------------------------------------------
                Analog v Digital configuration registers
     * ---------------------------------------------------------------*/
    
#ifdef _18F45K50
    ANSELE = 0x07;
    ANSELD = 0xFF;
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x00;
#endif
    
    /* ---------------------- A/D Converters: --------------------
     *  AN0     = A/D, Vref+ = Vdd,  Vref- + Vss
     * 
     *  ADCON2: Right Justified, Clock = Fosc, Acu Time = 2Tad
     * ----------------------------------------------------------  */
#ifdef _18F2455
    ADCON1 = 0x0e;      // AN0 as Analog. All rest digital
#endif

#ifdef _18F45K50
    WPUB = 0x00;        // Weak Pull-Ups on port B
    INTCONbits.IOCIF = 0; // Interrupt-On-Change
#endif
    
    INTCON2bits.nRBPU = 1;  // 1 = disable Reg B Pull-ups
}

/** -----------------  End of File ---------------------*/