/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CommonRoutines_H
#define	CommonRoutines_H


#ifndef Timer0_H
void Timer0_Init(void);
void Timer0_ISR(void);
void Timer0_Reset(void);

#endif

#ifndef Timer1_H
void Timer1_Init(void);
void Timer1_ISR(void);
void Timer1_Reset(void);
#endif

#ifndef Timer2_H
void Timer2_Init(void);
void Timer2_ISR(void);
void StartDepthDetection (void);
void EndDepthDetection (void);
#endif

#ifndef Timer3_H
void Timer3_Init(void);
void Timer3_ISR (void);
#endif

#ifndef CCP1_H
void CCP1_Init  (void);
void CCP1_ISR   (void);
#endif

#ifndef CCP2_H
void CCP2_Init  (void);
void CCP2_ISR   (void);
#endif

void ComputeWaterVol (void);

#endif	/* CommonRoutines_H */

