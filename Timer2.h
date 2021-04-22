/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Timer2_H
#define	Timer2_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TCON2: PostScaler : 10d (-1)  TMR2ON: Off   T2CKPS 1:16
#define     T2CON_Val   0x40

// PR2:  0x31 = 49 (50 - 1))
#define     PR2_Val     0x31

#endif	/* Timer2_H */

