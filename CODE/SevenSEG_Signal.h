/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : SevenSEG_Signal.h
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : BitsIO
**     Version   : Component 02.102, Driver 03.13, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**         This component "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**         Note: This component is set to work in Output direction only.
**     Settings  :
**         Port name                   : S
**
**         Bit mask of the port        : $00F0
**         Number of bits/pins         : 4
**         Single bit numbers          : 0 to 3
**         Values range                : 0 to 15
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 15 = 00FH
**         Initial pull option         : off
**
**         Port data register          : PTS       [$0248]
**         Port control register       : DDRS      [$024A]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    93   |   PS4_MISO0
**                    1      |    94   |   PS5_MOSI0
**                    2      |    95   |   PS6_SCK0
**                    3      |    96   |   PS7_SS0
**             ----------------------------------------------------
**
**         Optimization for            : code size
**     Contents  :
**         PutVal - void SevenSEG_Signal_PutVal(byte Val);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef SevenSEG_Signal_H_
#define SevenSEG_Signal_H_

/* MODULE SevenSEG_Signal. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

#pragma CODE_SEG SevenSEG_Signal_CODE
/*
** ===================================================================
**     Method      :  SevenSEG_Signal_PutVal (component BitsIO)
**
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val        - Output value (0 to 15)
**     Returns     : Nothing
** ===================================================================
*/
void SevenSEG_Signal_PutVal(byte Val);

#pragma CODE_SEG DEFAULT

/* END SevenSEG_Signal. */
#endif /* #ifndef __SevenSEG_Signal_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
