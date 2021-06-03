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
    
    __delay_ms(15);         // Allow LCD to power-up reset
    
#if (LCD_BusSize == 4)
    iCmd = LCD_CmdFunctionSet | LCD_FS_8Bit | LCD_FS_2Lines | LCD_FS_5x10;
    LCD_WriteNibble (iCmd >> 4);
    __delay_ms(5);
    LCD_WriteNibble (iCmd >> 4);
    __delay_us(100);
    LCD_WriteNibble (iCmd >> 4);
    
    iCmd = LCD_CmdFunctionSet | LCD_FS_4Bit | LCD_FS_2Lines | LCD_FS_5x10;
    LCD_WriteNibble (iCmd >>4);
    __delay_us(40);
    LCD_WriteCmd (iCmd, LCD_Delay_FunctSet);
#else
    iCmd = LCD_CmdFunctionSet | LCD_FS_8Bit | LCD_FS_2Lines | LCD_FS_5x10;
    LCD_WriteCmd (iCmd, LCD_Delay_FunctSet);
#endif
    
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

    Nop();
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

#if (LCD_BusSize == 4)
    LCD_WriteNibble(iCmd >> 4);
    LCD_WriteNibble(iCmd);
#else
    LCD_Enable();
    LATB = iCmd;
    LATC6 = iCmd >> 6;
    LATC7 = iCmd >> 7;
    LCD_Disable();
#endif
    //for(int i=0; i<iDelay; i++)
    //    __delay_us(1);
    LCD_WaitNotBusy();
}

void LCD_WriteChar(uint8_t iChar)
{
    LCD_SetData();
    LCD_SetWrite();

#if (LCD_BusSize == 4)
    LCD_WriteNibble (iChar >> 4);
    LCD_WriteNibble (iChar);
#else
    LCD_Enable();
    LATB = iChar;
    LATC6 = iChar >> 6;
    LATC7 = iChar >> 7;
    LCD_Disable();
#endif
    //__delay_us(LCD_Delay_WriteData);
    LCD_WaitNotBusy();
}

void LCD_WriteNibble(uint8_t iChar)
{
    LCD_Enable();
    LATBbits.LATB4 = iChar;
    LATBbits.LATB5 = iChar >> 1;
    LATCbits.LATC6 = iChar >> 2;
    LATCbits.LATC7 = iChar >> 3;
    LCD_Disable();
    //__delay_us (LCD_Delay_WriteData);
    LCD_WaitNotBusy();
    
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
                iData[i] = 0x20;        // Space
            }
            else
                sLine[i] = iData[i];
        } else
            sLine[i] = 0x20;            // Space
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
    //__delay_us(LCD_Delay_ClearDisp);
    LCD_WaitNotBusy();
}

void LCD_WaitNotBusy()
{
    TRISCbits.RC7 = 1;          // Make RC7 an input
    LCD_SetRead();              // Tell LCD we want to read
    LCD_SetCmd();               // Command State (RS->0)
    while (PORTCbits.RC7) Nop();// Wait for Not busy
    LCD_SetWrite();             // Return to default write mode
    TRISCbits.RC7 = 0;          // Return RC7 to an output
}