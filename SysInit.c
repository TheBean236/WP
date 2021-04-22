/*
 *  Function:   SysInit     - Initial Startup
 *              OscInit     - Set Master Oscillator
 */
#include <xc.h>

void OscInit(void);
void PIN_MANAGER_Initialize(void);

void SysInit (void)
{

    PIN_MANAGER_Initialize();
    OscInit();
}

void OscInit(void)
{
    // SCS FOSC; IDLEN disabled; IRCF 250KHz; 
    OSCCON = 0x10;
    // INTSRC INTRC_31_25KHz; PLLEN disabled; PRISD disabled; SOSCGO disabled; 
    OSCCON2 = 0x00;
    // SPLLMULT 4xPLL; TUN 0; 
    OSCTUNE = 0x00;
    // ACTSRC SOSC; ACTUD enabled; ACTEN disabled; 
    ACTCON = 0x00;
}


/**
 End of File
*/
