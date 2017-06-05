/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : US1_trigger.h
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.14, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This component is set to work in Output direction only.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       34            |  PH5_KWH5_MOSI2_TxD4
**             ----------------------------------------------------
**
**         Port name                   : H
**
**         Bit number (in port)        : 5
**         Bit mask of the port        : $0020
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTH       [$0260]
**         Port control register       : DDRH      [$0262]
**
**         Optimization for            : code size
**     Contents  :
**         ClrVal - void US1_trigger_ClrVal(void);
**         SetVal - void US1_trigger_SetVal(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef US1_trigger_H_
#define US1_trigger_H_

/* MODULE US1_trigger. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

#pragma CODE_SEG US1_trigger_CODE
/*
** ===================================================================
**     Method      :  US1_trigger_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define US1_trigger_ClrVal() ( \
    (void)clrReg8Bits(PTH, 0x20U)      /* PTH5=0x00U */ \
  )

/*
** ===================================================================
**     Method      :  US1_trigger_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define US1_trigger_SetVal() ( \
    (void)setReg8Bits(PTH, 0x20U)      /* PTH5=0x01U */ \
  )

#pragma CODE_SEG DEFAULT

/* END US1_trigger. */
#endif /* #ifndef __US1_trigger_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/