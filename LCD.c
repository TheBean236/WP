/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "Master.h"
#include "LCD.h"

void LCD_Init(void)
{
    uint8_t iCmd;
    
    __delay_ms(15);         // Allow LCD to settle
    iCmd = LCD_CmdFunctionSet | LCD_FS_8Bit | LCD_FS_2Lines | LCD_FS_5x10;
    LCD_WriteCmd (iCmd, LCD_Delay_FunctSet);
    
    iCmd = LCD_CmdSetDisplay | LCD_SD_DisplayOff | LCD_SD_CursorOff | 
            LCD_SD_BlinkOff;
    LCD_WriteCmd (iCmd, LCD_Delay_SetDisp);
    
    iCmd = LCD_CmdInputSet | LCD_IS_DirInc | LCD_IS_NoShift;
    LCD_WriteCmd (iCmd, LCD_Delay_InputSet);
    
    LCD_WriteCmd (LCD_CmdClearDisp, LCD_Delay_ClearDisp);
    
    iCmd = LCD_CmdSetDisplay | LCD_SD_DisplayOn | LCD_SD_CursorOff | 
            LCD_SD_BlinkOff;
    LCD_WriteCmd (iCmd,  LCD_Delay_SetDisp);
}

void LCD_WriteCmd (uint8_t iCmd, uint16_t iDelay)
{
    LCD_SetCmd();
    LCD_SetWrite();
    LATB = iCmd;
    LATC6 = iCmd>>6;
    LATC7 = iCmd>>7;
    LCD_Enable();
    LCD_Disable();  // Latches the command
    for (int i = 0; i<iDelay; i++)
        __delay_us(1);
}

void LCD_WriteChar(uint8_t iChar)
{
    LCD_SetData();
    LCD_SetWrite();

    LCD_Enable();
    LATB = iChar;
    LATC6 = iChar>>6;
    LATC7 = iChar>>7;
    LCD_Disable();  // Latches the data
    __delay_us(LCD_Delay_WriteData);
}

void LCD_WriteString (uint8_t *iData)
{
    uint8_t ix = 0;
    while (iData[ix]) {
        LCD_WriteChar (iData[ix]);
        ix ++;
    }
}

void LCD_GoTo (uint8_t iLine, uint8_t iCharPos)
{
    uint8_t iPos;
    if (iLine < 2)
       iPos = (iLine == 0) ? 
           (LCD_Line1_Start_Addr | iCharPos)   :
           (LCD_Line2_Start_Addr | iCharPos);
    LCD_WriteCmd (LCD_CmdSetDAddr | iPos, LCD_Delay_WriteData);
}

void LCD_ClearScreen ()
{
    LCD_WriteCmd (LCD_CmdClearDisp, LCD_Delay_ClearDisp);
    __delay_us(LCD_Delay_ClearDisp);
}

void LCD_Busy()
{
    TRISBbits.RB7 = 1;          // Make RB7 an input
    LCD_SetRead();              // Tell LCD we want to read
    LCD_SetCmd();               // Command State (RS->0)
    while (PORTBbits.RB7){
        LCD_Enable();
        LCD_Disable();
    }
    LCD_SetWrite();             // Return to default write mode
    TRISBbits.RB7 = 0;          // Return RB7 to an output
}