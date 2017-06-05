/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : IR_Emitter.h
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : PWM
**     Version   : Component 02.231, Driver 01.16, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**         This component implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
**     Comment   :
**         7843Hz
**     Settings  :
**         Used output pin             : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       4             |  PP0_KWP0_PWM0_MISO1_TIMIOC0
**             ----------------------------------------------------
**
**         Timer name                  : PWM0 [8-bit]
**         Counter                     : PWMCNT0   [$030C]
**         Mode register               : PWMCTL    [$0305]
**         Run register                : PWME      [$0300]
**         Prescaler                   : PWMPRCLK  [$0303]
**         Compare 1 register          : PWMPER0   [$0314]
**         Compare 2 register          : PWMDTY0   [$031C]
**         Flip-flop 1 register        : PWMPOL    [$0301]
**
**         User handling procedure     : not specified
**
**         Output pin
**
**         Port name                   : P
**         Bit number (in port)        : 0
**         Bit mask of the port        : $0001
**         Port data register          : PTP       [$0258]
**         Port control register       : DDRP      [$025A]
**
**         Runtime setting period      : none
**         Runtime setting ratio       : calculated
**         Initialization:
**              Aligned                : Left
**              Output level           : high
**              Timer                  : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 2000000 Hz
**           Initial value of            period        pulse width (ratio 5.882%)
**             Xtal ticks              : 510           30
**             microseconds            : 128           8
**             seconds (real)          : 0.0001275     0.0000075
**
**     Contents  :
**         Enable    - byte IR_Emitter_Enable(void);
**         Disable   - byte IR_Emitter_Disable(void);
**         SetRatio8 - byte IR_Emitter_SetRatio8(byte Ratio);
**         SetDutyUS - byte IR_Emitter_SetDutyUS(word Time);
**         SetValue  - byte IR_Emitter_SetValue(void);
**         ClrValue  - byte IR_Emitter_ClrValue(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __IR_Emitter
#define __IR_Emitter

/* MODULE IR_Emitter. */

#include "Cpu.h"

#pragma CODE_SEG IR_Emitter_CODE

#define IR_Emitter_PERIOD_VALUE 0xFFUL /* Initial period value in ticks of the timer */
#define IR_Emitter_PERIOD_VALUE_HIGH 0xFFUL /* Initial period value in ticks of the timer in high speed mode */

byte IR_Emitter_Enable(void);
/*
** ===================================================================
**     Method      :  IR_Emitter_Enable (component PWM)
**
**     Description :
**         This method enables the component - it starts the signal
**         generation. Events may be generated (<DisableEvent>
**         /<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte IR_Emitter_Disable(void);
/*
** ===================================================================
**     Method      :  IR_Emitter_Disable (component PWM)
**
**     Description :
**         This method disables the component - it stops the signal
**         generation and events calling. When the timer is disabled,
**         it is possible to call <ClrValue> and <SetValue> methods.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte IR_Emitter_SetRatio8(byte Ratio);
/*
** ===================================================================
**     Method      :  IR_Emitter_SetRatio8 (component PWM)
**
**     Description :
**         This method sets a new duty-cycle ratio. The ratio is
**         expressed as an 8-bit unsigned integer number. Value 0 - 255
**         is proportional to ratio 0 - 100%. 
**         Note: Calculated duty depends on the timer possibilities and
**         on the selected period.
**         The method is available only if method <SetPeriodMode> is
**         not selected.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Ratio           - Ratio to set. 0 - 255 value is
**                           proportional to ratio 0 - 100%
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte IR_Emitter_SetDutyUS(word Time);
/*
** ===================================================================
**     Method      :  IR_Emitter_SetDutyUS (component PWM)
**
**     Description :
**         This method sets the new duty value of the output signal. The
**         duty is expressed in microseconds as a 16-bit unsigned integer
**         number.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Time       - Duty to set [in microseconds]
**                      (0 to 128 us in high speed mode)
**     Returns     :
**         ---        - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

byte IR_Emitter_SetValue(void);
/*
** ===================================================================
**     Method      :  IR_Emitter_SetValue (component PWM)
**
**     Description :
**         This method sets (to "1" = "High") timer flip-flop output
**         signal level. It allows to the user to directly set the
**         output pin value (=flip-flop state), and can set the signal
**         polarity. This method only works when the timer is disabled
**         (Disable) otherwise it returns the error code. <ClrValue>
**         and <SetValue> methods are used for setting the initial
**         state.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_ENABLED - Component is enabled.
**                           Component must be disabled (see "Disable
**                           method")
** ===================================================================
*/

byte IR_Emitter_ClrValue(void);
/*
** ===================================================================
**     Method      :  IR_Emitter_ClrValue (component PWM)
**
**     Description :
**         This method clears (sets to "0" = "Low") timer flip-flop
**         output signal level. It allows to the user to directly set
**         the output pin value (=flip-flop state), and can set the
**         signal polarity. This method only works when the timer is
**         disabled (Disable) otherwise it returns the error code.
**         <ClrValue> and <SetValue> methods are used for setting the
**         initial state.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_ENABLED - Component is enabled.
**                           Component must be disabled (see "Disable
**                           method")
** ===================================================================
*/

void IR_Emitter_Init(void);
/*
** ===================================================================
**     Method      :  IR_Emitter_Init (component PWM)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT

/* END IR_Emitter. */

#endif /* ifndef __IR_Emitter */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
