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

// CCP1 
void CCP1_Init  (void);
void CCP1_ISR   (void);
void CCP1_Activate (void);

#ifndef CCP2_H
void CCP2_Init  (void);
void CCP2_ISR   (void);
#endif

// A/D Convertsr
void AN0_Init       (void);
void AN0_ISR        (void);
void CaptureTemp    (void);
void ComputeTemp    (void);

void ComputeWaterVol (void);

#ifndef LCD_h
void LCD_Init           (void);
void LCD_DisplayResults (void);
void LCD_WriteChar      (uint8_t iChar);
void LCD_WriteCmd       (uint8_t iCmd, uint16_t iDelay);
void LCD_WriteString    (uint8_t *iData);
void LCD_WriteLine      (uint8_t *iData);
void LCD_ClearScreen    (void);
void LCD_GoTo           (uint8_t iLine, uint8_t iPos);
void LCD_Busy           (void);
#endif
#endif	/* CommonRoutines_H */

