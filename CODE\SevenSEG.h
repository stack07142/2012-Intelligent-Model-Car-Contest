/** ###################################################################
**     Filename  : SevenSEG.h
**     Project   : SCC_01
**     Processor : MC9S12XEP100CAL
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-06-28, ¿ÀÈÄ 2:35
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __SevenSEG_H
#define __SevenSEG_H

/* MODULE SevenSEG */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"
#include "SevenSEG_Data.h"
#include "SevenSEG_Signal.h"

#pragma DATA_SEG SevenSEG_DATA
#pragma CODE_SEG SevenSEG_CODE
#pragma CONST_SEG SevenSEG_CONST
#define ABS(x)          ( (x)<(0) ?(-(x)) : (x) )

#pragma CODE_SEG SevenSEG_CODE
byte NumToSeg(int a);


/* END SevenSEG */

#endif

