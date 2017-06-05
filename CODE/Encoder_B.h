/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Encoder_B.h
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : PulseAccumulator
**     Version   : Component 01.185, Driver 01.19, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**     Settings  :
**             Pulse accumulator       : ECTPACNT01
**
**              Pulse accumulator      : Enabled
**              Events                 : Enabled
**              Overwrite mode         : Disabled
**
**         Timer registers
**              Counter                : ECT_PACN10 [$0064]
**              Hold                   : ECT_PA10H [$0074]
**              Mode                   : ECT_ICOVW [$006A]
**              Run                    : ECT_PBCTL [$0070]
**
**         User handling procedure     : not specified
**
**     Contents  :
**         Enable          - byte Encoder_B_Enable(void);
**         Disable         - byte Encoder_B_Disable(void);
**         ResetCounter    - void Encoder_B_ResetCounter(void);
**         GetCounterValue - Encoder_B_TCounterValue Encoder_B_GetCounterValue(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __Encoder_B
#define __Encoder_B

/* MODULE Encoder_B. */

#include "Cpu.h"

#pragma CODE_SEG Encoder_B_CODE
#pragma DATA_SEG Encoder_B_DATA        /* Select data segment "Encoder_B_DATA" */

#ifndef __BWUserType_Encoder_B_TCounterValue
#define __BWUserType_Encoder_B_TCounterValue
typedef word Encoder_B_TCounterValue;  /* Counter value, width depends on selected peripheal. */
#endif

byte Encoder_B_Enable(void);
/*
** ===================================================================
**     Method      :  Encoder_B_Enable (component PulseAccumulator)
**
**     Description :
**         Enables the component.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
** ===================================================================
*/

byte Encoder_B_Disable(void);
/*
** ===================================================================
**     Method      :  Encoder_B_Disable (component PulseAccumulator)
**
**     Description :
**         Disables the component.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
** ===================================================================
*/

#define Encoder_B_ResetCounter() ( \
  ECT_PACN10 = 0U\
)
/*
** ===================================================================
**     Method      :  Encoder_B_ResetCounter (component PulseAccumulator)
**
**     Description :
**         This method resets the pulse accumulator counter (sets to
**         zero).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define Encoder_B_GetCounterValue() (ECT_PACN10)
/*
** ===================================================================
**     Method      :  Encoder_B_GetCounterValue (component PulseAccumulator)
**
**     Description :
**         This method returns the content of the pulse accumulator
**         counter.
**     Parameters  : None
**     Returns     :
**         ---             - Content of the counter register.
** ===================================================================
*/

void Encoder_B_Init(void);
/*
** ===================================================================
**     Method      :  Encoder_B_Init (component PulseAccumulator)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma DATA_SEG DEFAULT               /* Select data segment "DEFAULT" */
#pragma CODE_SEG DEFAULT

/* END Encoder_B. */

#endif /* ifndef __Encoder_B */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/