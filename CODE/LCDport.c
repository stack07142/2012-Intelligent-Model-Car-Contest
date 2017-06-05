/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : LCDport.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : ByteIO
**     Version   : Component 02.058, Driver 03.15, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**         This component "ByteIO" implements an one-byte input/output.
**         It uses one 8-bit port.
**         Note: This component is set to work in Output direction only.
**         Methods of this component are mostly implemented as a macros 
**         (if supported by target langauage and compiler).
**     Settings  :
**         Port name                   : B
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         8-bit data register         : PORTB     [$0001]
**         8-bit control register      : DDRB      [$0003]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    24   |   PB0
**                    1      |    25   |   PB1
**                    2      |    26   |   PB2
**                    3      |    27   |   PB3
**                    4      |    28   |   PB4
**                    5      |    29   |   PB5
**                    6      |    30   |   PB6
**                    7      |    31   |   PB7
**             ----------------------------------------------------
**     Contents  :
**         GetDir - bool LCDport_GetDir(void);
**         GetVal - byte LCDport_GetVal(void);
**         PutVal - void LCDport_PutVal(byte Val);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE LCDport. */

#include "LCDport.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

#pragma DATA_SEG LCDport_DATA          /* Select data segment "LCDport_DATA" */
#pragma CODE_SEG LCDport_CODE
#pragma CONST_SEG LCDport_CONST        /* Constant section for this module */
/*
** ===================================================================
**     Method      :  LCDport_GetVal (component ByteIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pins and returns it
**           b) direction = Output : returns the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---        - Input value (0 to 255)
** ===================================================================
*/
/*
byte LCDport_GetVal(void)

**  This method is implemented as a macro. See LCDport.h file.  **
*/

/*
** ===================================================================
**     Method      :  LCDport_PutVal (component ByteIO)
**
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val        - Output value (0 to 255)
**     Returns     : Nothing
** ===================================================================
*/
/*
void LCDport_PutVal(byte Val)

**  This method is implemented as a macro. See LCDport.h file.  **
*/

/*
** ===================================================================
**     Method      :  LCDport_GetDir (component ByteIO)
**
**     Description :
**         This method returns direction of the component.
**     Parameters  : None
**     Returns     :
**         ---        - Direction of the component (always TRUE, Output only)
**                      FALSE = Input, TRUE = Output
** ===================================================================
*/
/*
bool LCDport_GetDir(void)

**  This method is implemented as a macro. See LCDport.h file.  **
*/


/* END LCDport. */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
