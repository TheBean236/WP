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

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISE = 0x07;
    TRISA = 0xD0;
    TRISB = 0x00;
    TRISC = 0x84;
    TRISD = 0xFF;
    TRISCbits.RC0 = 0;
    TRISCbits.RC6 =     0;
    TRISCbits.RC7   = 0;

    /**
    ANSELx registers
    */
    ANSELD = 0xFF;
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELE = 0x07;
    ANSELA = 0x00;

    /**
    WPUx registers
    */
    WPUB = 0x00;
    INTCON2bits.nRBPU = 1;
    PIN_MANAGER_IOC();
}
  
void PIN_MANAGER_IOC(void)
{   
	// Clear global Interrupt-On-Change flag
    INTCONbits.IOCIF = 0;
}

/**
 End of File
*/