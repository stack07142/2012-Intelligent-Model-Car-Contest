/** ###################################################################
**     Filename  : SevenSEG.c
**     Project   : SCC_01
**     Processor : MC9S12XEP100CAL
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-06-28, ¿ÀÈÄ 2:35
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE SevenSEG */
#include "SevenSEG.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

#pragma DATA_SEG SevenSEG_DATA   /* Select data segment "SevenSEG_DATA" */
#pragma CODE_SEG SevenSEG_CODE
#pragma CONST_SEG SevenSEG_CONST   /* Constant section for this module */
/*
static const byte SevenSEG_Table[10] = {   // Table of Number constants //
  0X3FU, 0x06U, 0x5BU, 0x4FU, 0x66U, 0x6DU, 0x7CU, 0x07U, 0x7FU, 0x57U  
};
*/

//ASDF
static const byte SevenSEG_Table[10] = {   // Table of Number constants //
  0XEBU, 0x28U, 0xB3U, 0xBAU, 0x78U, 0xDAU, 0xDBU, 0xE8U, 0xFBU, 0xFAU  
};

#pragma CODE_SEG SevenSEG_CODE

byte NumToSeg(int a)
{
  return (byte)((a<10) ? SevenSEG_Table[a] : 0x04U);
}

/*
byte NumToSeg(int a){
  // asdf
  switch(a){
    case 0: return 0b11101011;   //0xEB
    case 1: return 0b00101000;   //0x28
    case 2: return 0b10110011;   //0xB3
    case 3: return 0b10111010;   //0xBA
    case 4: return 0b01111000;   //0x78
    case 5: return 0b11011010;   //0xDA
    case 6: return 0b11011011;   //0xDB
    case 7: return 0b11101000;   //0xE8
    case 8: return 0b11111011;   //0xFB
    case 9: return 0b11111010;   //0xFA
    default : return 0b00000100;  //0x04
  }

}
*/

/* END SevenSEG */

