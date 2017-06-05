/** ###################################################################
**     Filename  : LCD.h
**     Project   : SCC_01
**     Processor : MC9S12XEP100CAL
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-06-27, ¿ÀÈÄ 8:02
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __LCD_H
#define __LCD_H

/* MODULE LCD */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"
#include "LCDport.h"

#pragma DATA_SEG LCD_DATA

#pragma CODE_SEG LCD_CODE

#pragma CONST_SEG LCD_CONST

#define LCD_DDR DDRB
#define LCD_PORT PORTB

#define US_CONST 8U       // system clock 16MHz //
#define MS_CONST 8000U    // system clock 16MHz //


#define FUNCTION_SET 0x28U
#define DISPLAY_ON 0x0CU
#define ENTRYMODE_SET 0x06U
#define CURSOR_HOME 0x02U
#define LCD_CLEAR 0x01U


#define ENABLE    (setReg8Bits(LCD_PORT, 0x04U))
#define DISABLE   (clrReg8Bits(LCD_PORT, 0x04U))

#define RS_ON     (setReg8Bits(LCD_PORT, 0x01U))
#define RS_OFF    (clrReg8Bits(LCD_PORT, 0x01U))


/*
#define ENABLE (LCD_PORT |= 0x04)
#define DISABLE (LCD_PORT &= ~0x04)

#define RS_ON (LCD_PORT |= 0x01)
#define RS_OFF (LCD_PORT &= ~0x01)
*/


// function prototypes... //
void instructionSet(unsigned char data);
void initLCD(void);
void charDisp(unsigned char data);
void stringDisp(unsigned char* str, int y);


#endif __LCD_H
