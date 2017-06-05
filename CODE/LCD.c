/** ###################################################################
**     Filename  : LCD.c
**     Project   : SCC_01
**     Processor : MC9S12XEP100CAL
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-06-27, ¿ÀÈÄ 8:02
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE LCD */

#include "LCD.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma DATA_SEG LCD_DATA   /* Select data segment "LCD_DATA" */
#pragma CODE_SEG LCD_CODE
#pragma CONST_SEG LCD_CONST   /* Constant section for this module */

#pragma CODE_SEG LCD_CODE

// static functions delay... //

static void _delay_ms(int a)
{
  volatile int i, j;
  
  for(j=0;j<a;j++){
    for(i=0;i<MS_CONST;i++){    
    }
  }
  
 
}

static void _delay_us(int a)
{
  volatile int i, j;
  
  for(j=0;j<a;j++){
    for(i=0;i<US_CONST;i++){    
    }
  }
  
  
}


// user interface functions... //

void instructionSet(unsigned char data)
{
	// Foward 4-bit
	LCD_PORT = 0xF0 & data;

	ENABLE;
	_delay_us(20);
	DISABLE;

	// Backwart 4-bit
	LCD_PORT = (0x0F & data) << 4;

	ENABLE;
	_delay_us(20);
	DISABLE;
}

void initLCD(void)
{
	LCD_DDR = 0xFF;
	LCD_PORT = 0x20;

	ENABLE;
	_delay_us(20);
	DISABLE;

  instructionSet(0x20);
  _delay_us(100);
	instructionSet(FUNCTION_SET);
	_delay_us(100);
	instructionSet(DISPLAY_ON);
	_delay_us(100);
	instructionSet(ENTRYMODE_SET);
	_delay_us(100);
	instructionSet(LCD_CLEAR);
	_delay_ms(2);
	instructionSet(CURSOR_HOME);
	_delay_us(100);
}

void charDisp(unsigned char data)
{
	// Forward 4-bit
	LCD_PORT = 0xF0 & data;

	RS_ON;
	ENABLE;
	_delay_us(20);
	DISABLE;
	RS_OFF;

	// Backward 4-bit
	LCD_PORT = (0x0F & data) << 4;
	
	RS_ON;
	ENABLE;
	_delay_us(20);
	DISABLE;
	RS_OFF;
}	

void stringDisp(unsigned char* str, int y)
{
	volatile int i;

	//instructionSet(y?0xc0:0x80);
	
	//for(i=0;i<16;i++) charDisp(' ');

	instructionSet(y?0xc0:0x80);

	for(i=0;str[i]!='\0';i++) charDisp(str[i]);

	instructionSet(CURSOR_HOME);
	_delay_us(20);
}



