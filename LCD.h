/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_h
#define	LCD_h

#include <xc.h> // include processor files - each processor file is guarded.  

//  Enable:     A1
//  R/W         A2
//  RS          A3
#define LCD_SetCmd()    do { LATAbits.LATA3 = 0; } while(0)
#define LCD_SetData()   do { LATAbits.LATA3 = 1; } while(0)
#define LCD_Enable()    do { LATAbits.LATA1 = 1; } while(0)
#define LCD_Disable()   do { LATAbits.LATA1 = 0; } while(0)
#define LCD_SetRead()   do { LATAbits.LATA2 = 1; } while(0)
#define LCD_SetWrite()  do { LATAbits.LATA2 = 0; } while(0)

// Command Set
#define LCD_CmdClearDisp    0x01
#define LCD_CmdGoHome       0x02
//      Input Set
#define LCD_CmdInputSet     0x04
#define LCD_IS_DirInc       0x02
#define LCD_IS_DirDec       0x00
#define LCD_IS_Shift        0x01
#define LCD_IS_NoShift      0x00
//      Set Display
#define LCD_CmdSetDisplay   0x08
#define LCD_SD_DisplayOn    0x04
#define LCD_SD_DisplayOff   0x00
#define LCD_SD_CursorOn     0x02
#define LCD_SD_CursorOff    0x00
#define LCD_SD_BlinkOn      0x01
#define LCD_SD_BlinkOff     0x00
//      Shift
#define LCD_CmdShift        0x10
#define LCD_S_ShiftDisplay  0x08
#define LCD_S_ShiftCusor    0x00
#define LCD_S_Right         0x04
#define LCD_S_Left          0x00
//      Function Set
#define LCD_CmdFunctionSet  0x20
#define LCD_FS_8Bit         0x10
#define LCD_FS_4Bit         0x00
#define LCD_FS_2Lines       0x08
#define LCD_FS_1Line        0x00
#define LCD_FS_5x10         0x04
#define LCD_FS_5x7          0x00

//      Set Addresses
#define LCD_CmdSetGAddr         0x40
#define LCD_CmdSetDAddr         0x80

// Command Execution Delays (uS)
//   10 us added to some to provide a buffer
#define LCD_Delay_ClearDisp     2000
#define LCD_Delay_RetHome       2000
#define LCD_Delay_InputSet      40+10
#define LCD_Delay_SetDisp       40+10
#define LCD_Delay_Shift         40+10
#define LCD_Delay_FunctSet      40+10
#define LCD_Delay_SetDAddr      40+10
#define LCD_Delay_WriteData     40+10
#define LCD_Delay_Busy          1

// DDRAM Line Starting Addresses
#define LCD_Line1_Start_Addr    0x80
#define LCD_Line2_Start_Addr    0xC0

void LCD_Init           (void);
void LCD_WriteChar      (uint8_t iChar);
void LCD_WriteCmd       (uint8_t iCmd, uint16_t iDelay);
void LCD_WriteString    (uint8_t *iData);
void LCD_WriteLine      (uint8_t *iData);
void LCD_ClearScreen    (void);
void LCD_GoTo           (uint8_t iLine, uint8_t iPos);
void LCD_Busy           (void);
#endif	/* LCD_h */

