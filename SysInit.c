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
    // 45K50: SCS FOSC; IDLEN disabled; IRCF 250KHz;
    // 2455:    IRCF = 125Khz
    // 24K50 IRCF is 2x the 2455 value 
    OSCCON = 0x10;
    
#ifdef _18F24K50
    // 2455 does not have OSCCON2 or ACTCON registers
    // INTSRC INTRC_31_25KHz; PLLEN disabled; PRISD disabled; SOSCGO disabled; 
    OSCCON2 = 0x00;
    // ACTSRC SOSC; ACTUD enabled; ACTEN disabled; 
    ACTCON = 0x00;
#endif
    // SPLLMULT 4xPLL; TUN 0; 
    OSCTUNE = 0x00;
}

/* -----------------  USB CLOCK SETTINGS 2455 -----------------
 * The USB clock needs to be 48Mhz and runs of the PLL
 * PLL Input must be 4Mhz.
 * The following sets the USB clock independent of the CPU
 * To setup:
 *  . Set PLLDIV to divide crytal freq to get 4 Mhz
 *  . Set USBDIV to 1 (unless using a 48Mhz crystal)
 *  . Set FSEN to 1
 *      This maps the PLL to the USB clock independent of CPU
 *  . HS, XT, EC, ECIO drives system clock from Crystal
 *  . HSPLL, ECPLL, XTPLL, ECPIO drives system clock from PLL
 *  . 
 * ------------------------------------------------------------*/
/* -------------------- End of File ---------------------- */
