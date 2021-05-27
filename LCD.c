/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#include <stdio.h>
#include <string.h>
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

void LCD_DisplayResults ()
{
    LCD_GoTo (0, 0);
    sprintf(sLine1, "Gals:%4u  %3u%% ", giGals, giPercentFull);
    LCD_WriteLine (sLine1);

    LCD_GoTo(1, 0);
    sprintf(sLine2, "Echo:%4u %2u/%2u", giEmptySpace_mm, 
            giAirTempC, giAirTempF);
    LCD_WriteLine (sLine2);
    Nop();                      // Allows setting a breakpoint
}

void LCD_WriteCmd (uint8_t iCmd, uint16_t iDelay)
{
    LCD_SetCmd();
    LCD_SetWrite();
    LCD_Enable();
    LATB = iCmd;
    Pin_LCD_Data6 = iCmd>>6;
    Pin_LCD_Data7 = iCmd>>7;
    LCD_Disable();  // Latches the command
    for (uint8_t i = 0; i<iDelay; i++)
        __delay_us(1);
}

void LCD_WriteChar(uint8_t iChar)
{
    LCD_SetData();
    LCD_SetWrite();

    LCD_Enable();
    LATB = iChar;
    Pin_LCD_Data6 = iChar>>6;
    Pin_LCD_Data7 = iChar>>7;
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
void LCD_WriteLine (uint8_t *iData)
{
    int i;
    uint8_t sLine[17];
    bool bInString = true;
    
    
    for (i = 0; i < 16; i++)
    {
        if (bInString)
        {
            if (iData[i] == 0)
            {
                bInString = false;
                iData[i] = " ";
            }
            else
                sLine[i] = iData[i];
        } else
            sLine[i] = " ";
    }
    sLine[i] = 0;
    LCD_WriteString (sLine);
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
    /*
    TRISBbits.RB7 = 1;          // Make RB7 an input
    LCD_SetRead();              // Tell LCD we want to read
    LCD_SetCmd();               // Command State (RS->0)
    while (PORTBbits.RB7){
        LCD_Enable();
        LCD_Disable();
    }
    LCD_SetWrite();             // Return to default write mode
    TRISBbits.RB7 = 0;          // Return RB7 to an output
     * */
}