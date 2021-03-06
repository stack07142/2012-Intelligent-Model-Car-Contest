/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : ExtInt_Rising.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : ExtInt
**     Version   : Component 02.094, Driver 01.20, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**         This component "ExtInt" implements an external 
**         interrupt, its control methods and interrupt/event 
**         handling procedure.
**         The component uses one pin which generates interrupt on 
**         selected edge.
**     Settings  :
**         Interrupt name              : Vporth
**         User handling procedure     : ExtInt_Rising_OnInterrupt
**
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       52            |  PH0_KWH0_MISO1_RxD6
**             ----------------------------------------------------
**
**         Port name                   : H
**
**         Bit number (in port)        : 0
**         Bit mask of the port        : $0001
**
**         Signal edge/level           : rising
**         Priority                    : 4
**         Pull option                 : off
**         Initial state               : Enabled
**
**         Edge register               : PPSH      [$0265]
**         Enable register             : PIEH      [$0266]
**         Request register            : PIFH      [$0267]
**
**         Port data register          : PTH       [$0260]
**         Port control register       : DDRH      [$0262]
**     Contents  :
**         Enable  - void ExtInt_Rising_Enable(void);
**         Disable - void ExtInt_Rising_Disable(void);
**         GetVal  - bool ExtInt_Rising_GetVal(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/


/* MODULE ExtInt_Rising. */

#include "ExtInt_Rising.h"
/*Including shared modules, which are used for all project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"

#pragma DATA_SEG ExtInt_Rising_DATA    /* Select data segment "ExtInt_Rising_DATA" */
#pragma CODE_SEG ExtInt_Rising_CODE

/*
** ===================================================================
**     Method      :  ExtInt_Rising_Enable (component ExtInt)
**
**     Description :
**         Enable the component - the external events are accepted.
**         This method is available only if HW module allows
**         enable/disable of the interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ExtInt_Rising_Enable(void)
{
  PIFH = 0x01U;                         /* Clear flag */
  PIEH_PIEH0 = 1U;                      /* Enable interrupt */
}

/*
** ===================================================================
**     Method      :  ExtInt_Rising_Disable (component ExtInt)
**
**     Description :
**         Disable the component - the external events are not accepted.
**         This method is available only if HW module allows
**         enable/disable of the interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void ExtInt_Rising_Disable(void)

**  This method is implemented as a macro. See ExtInt_Rising.h file.  **

*/
/*
** ===================================================================
**     Method      :  ExtInt_Rising_GetVal (component ExtInt)
**
**     Description :
**         Returns the actual value of the input pin of the component.
**     Parameters  : None
**     Returns     :
**         ---             - Returned input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
** ===================================================================
*/
/*
bool ExtInt_Rising_GetVal(void)

**      This method is implemented as macro      **
*/

/* END ExtInt_Rising. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
