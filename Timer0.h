/* 
 * File:        Timer0.h
 * Author:      MBB
 * Comments:    Timer0 Globals (TOD Clock)
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Timer0_H
#define	Timer0_H

#include <xc.h> // include processor files - each processor file is guarded.  

uint16_t Timer0_Reload = ~(I_Clock / 1000 * 5 + 2);  

#endif	/* Timer0_H */

