/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : US_echo_timer.h
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

#ifndef __US_echo_timer
#define __US_echo_timer

/* MODULE US_echo_timer. */

#include "Cpu.h"

#pragma CODE_SEG US_echo_timer_CODE
#pragma DATA_SEG US_echo_timer_DATA    /* Select data segment "US_echo_timer_DATA" */


extern volatile bool US_echo_timer_EnEvent; /* Enable/Disable events */

byte US_echo_timer_Enable(void);
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

#define US_echo_timer_Disable() ( \
  (PITCE &= 0xFDU),                    /* Disable timer */ \
  ERR_OK                               /* Return result */ \
)
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

#define US_echo_timer_EnableEvent() (US_echo_timer_EnEvent = TRUE, ERR_OK) /* Set the flag "events enabled" */
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

#define US_echo_timer_DisableEvent() (US_echo_timer_EnEvent = FALSE, ERR_OK) /* Set the flag "events disabled" */
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

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void US_echo_timer_Interrupt(void);
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

#pragma DATA_SEG DEFAULT               /* Select data segment "DEFAULT" */
#pragma CODE_SEG DEFAULT

/* END US_echo_timer. */

#endif /* ifndef __US_echo_timer */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
