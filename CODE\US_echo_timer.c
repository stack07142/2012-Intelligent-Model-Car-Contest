/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : US_echo_timer.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : TimerInt
**     Version   : Component 02.159, Driver 01.20, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : PIT1 (16-bit)
**         Compare name                : PITload1
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 16000000 Hz
**           Initial period/frequency
**             Xtal ticks              : 40
**             microseconds            : 10
**             seconds (real)          : 0.00001
**             Hz                      : 100000
**             kHz                     : 100
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : PITCNT1   [$034E]
**              Mode                   : PITCFLMT  [$0340]
**              Run                    : PITCE     [$0342]
**
**         Compare registers
**              Compare                : PITLD1    [$034C]
**
**         Flip-flop registers
**     Contents  :
**         Enable       - byte US_echo_timer_Enable(void);
**         Disable      - byte US_echo_timer_Disable(void);
**         EnableEvent  - byte US_echo_timer_EnableEvent(void);
**         DisableEvent - byte US_echo_timer_DisableEvent(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE US_echo_timer. */

#include "Events.h"
#include "US_echo_timer.h"

#pragma DATA_SEG US_echo_timer_DATA    /* Select data segment "US_echo_timer_DATA" */
#pragma CODE_SEG US_echo_timer_CODE
#pragma CONST_SEG DEFAULT              /* Use default segment for constants */

volatile bool US_echo_timer_EnEvent;   /* Enable/Disable events */


/* Internal method prototypes */


/* End of Internal methods declarations */

/*
** ===================================================================
**     Method      :  US_echo_timer_Enable (component TimerInt)
**
**     Description :
**         This method enables the component - it starts the timer.
**         Events may be generated (<DisableEvent>/<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte US_echo_timer_Enable(void)
{
  PITTF = 0x02U;                       /* Reset interrupt request flag */ 
  PITINTE |= 0x02U;                    /* Enable interrupt */ 
  PITCE |= 0x02U;                      /* Enable timer */ 
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  US_echo_timer_Disable (component TimerInt)
**
**     Description :
**         This method disables the component - it stops the timer. No
**         events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte US_echo_timer_Disable(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  US_echo_timer_EnableEvent (component TimerInt)
**
**     Description :
**         This method enables the events.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte US_echo_timer_EnableEvent(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  US_echo_timer_DisableEvent (component TimerInt)
**
**     Description :
**         This method disables the events.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte US_echo_timer_DisableEvent(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  US_echo_timer_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(US_echo_timer_Interrupt)
{
  PITTF = 0x02U;                       /* Reset interrupt request flag */
  if (US_echo_timer_EnEvent) {         /* Are the events enabled? */
    US_echo_timer_OnInterrupt();       /* Invoke user event */
  }
}

#pragma CODE_SEG US_echo_timer_CODE

/* END US_echo_timer. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
