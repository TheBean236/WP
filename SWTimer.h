/* 
 * File:        SWTimer.h
 * Author:      Michael Bender
 * Comments:    We use TMR3 to time software modules
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SWTimer_H
#define	SWTimer_H

#define SWTimer_Start() {\
    TMR3H = 0;\
    TMR3L = 0;\
    T3CONbits.TMR3ON = 1;}

#define SWTimer_Stop() {T3CONbits.TMR3ON = 0;}
#define SWTimer_Read() {\
    gi_SW_Time = TMR3L;\
    gi_SW_Time += TMR3H << 8;}

#endif	/* SWTimer_H */

