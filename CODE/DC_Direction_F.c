/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : DC_Direction_F.c
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
**                       88            |  PM6_RxCAN3_RxCAN4_RxD3
**             ----------------------------------------------------
**
**         Port name                   : M
**
**         Bit number (in port)        : 6
**         Bit mask of the port        : $0040
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTM       [$0250]
**         Port control register       : DDRM      [$0252]
**
**         Optimization for            : code size
**     Contents  :
**         GetVal - bool DC_Direction_F_GetVal(void);
**         PutVal - void DC_Direction_F_PutVal(bool Val);
**         ClrVal - void DC_Direction_F_ClrVal(void);
**         SetVal - void DC_Direction_F_SetVal(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE DC_Direction_F. */

#include "DC_Direction_F.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

#pragma DATA_SEG DC_Direction_F_DATA   /* Select data segment "DC_Direction_F_DATA" */
#pragma CODE_SEG DC_Direction_F_CODE
#pragma CONST_SEG DC_Direction_F_CONST /* Constant section for this module */
/*
** ===================================================================
**     Method      :  DC_Direction_F_GetVal (component BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
/*
bool DC_Direction_F_GetVal(void)

**  This method is implemented as a macro. See DC_Direction_F.h file.  **
*/

/*
** ===================================================================
**     Method      :  DC_Direction_F_PutVal (component BitIO)
**
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void DC_Direction_F_PutVal(bool Val)
{
  if (Val) {
    setReg8Bits(PTM, 0x40U);           /* PTM6=0x01U */
  } else { /* !Val */
    clrReg8Bits(PTM, 0x40U);           /* PTM6=0x00U */
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  DC_Direction_F_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void DC_Direction_F_ClrVal(void)

**  This method is implemented as a macro. See DC_Direction_F.h file.  **
*/

/*
** ===================================================================
**     Method      :  DC_Direction_F_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void DC_Direction_F_SetVal(void)

**  This method is implemented as a macro. See DC_Direction_F.h file.  **
*/


/* END DC_Direction_F. */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
