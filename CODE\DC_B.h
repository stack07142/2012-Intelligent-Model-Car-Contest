/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : DC_B.h
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : PWM
**     Version   : Component 02.231, Driver 01.16, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-16, ���� 12:39
**     Abstract  :
**         This component implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
**     Settings  :
**         Used output pin             : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       111           |  PP5_KWP5_PWM5_MOSI2_TIMIOC5
**             ----------------------------------------------------
**
**         Timer name                  : PWM5 [8-bit]
**         Counter                     : PWMCNT5   [$0311]
**         Mode register               : PWMCTL    [$0305]
**         Run register                : PWME      [$0300]
**         Prescaler                   : PWMPRCLK  [$0303]
**         Compare 1 register          : PWMPER5   [$0319]
**         Compare 2 register          : PWMDTY5   [$0321]
**         Flip-flop 1 register        : PWMPOL    [$0301]
**
**         User handling procedure     : not specified
**
**         Output pin
**
**         Port name                   : P
**         Bit number (in port)        : 5
**         Bit mask of the port        : $0020
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
**             Clock                   : 31250 Hz
**           Initial value of            period        pulse width (ratio 0.4%)
**             Xtal ticks              : 32000         128
**             microseconds            : 8000          32
**             milliseconds            : 8             0
**             seconds (real)          : 0.008         0.000032
**
**     Contents  :
**         Enable    - byte DC_B_Enable(void);
**         Disable   - byte DC_B_Disable(void);
**         SetRatio8 - byte DC_B_SetRatio8(byte Ratio);
**         SetDutyUS - byte DC_B_SetDutyUS(word Time);
**         SetValue  - byte DC_B_SetValue(void);
**         ClrValue  - byte DC_B_ClrValue(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __DC_B
#define __DC_B

/* MODULE DC_B. */

#include "Cpu.h"

#pragma CODE_SEG DC_B_CODE

#define DC_B_PERIOD_VALUE    0xFAUL    /* Initial period value in ticks of the timer */
#define DC_B_PERIOD_VALUE_HIGH 0xFAUL  /* Initial period value in ticks of the timer in high speed mode */

byte DC_B_Enable(void);
/*
** ===================================================================
**     Method      :  DC_B_Enable (component PWM)
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

byte DC_B_Disable(void);
/*
** ===================================================================
**     Method      :  DC_B_Disable (component PWM)
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

byte DC_B_SetRatio8(byte Ratio);
/*
** ===================================================================
**     Method      :  DC_B_SetRatio8 (component PWM)
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

byte DC_B_SetDutyUS(word Time);
/*
** ===================================================================
**     Method      :  DC_B_SetDutyUS (component PWM)
**
**     Description :
**         This method sets the new duty value of the output signal. The
**         duty is expressed in microseconds as a 16-bit unsigned integer
**         number.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Time       - Duty to set [in microseconds]
**                      (0 to 8000 us in high speed mode)
**     Returns     :
**         ---        - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

byte DC_B_SetValue(void);
/*
** ===================================================================
**     Method      :  DC_B_SetValue (component PWM)
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

byte DC_B_ClrValue(void);
/*
** ===================================================================
**     Method      :  DC_B_ClrValue (component PWM)
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

void DC_B_Init(void);
/*
** ===================================================================
**     Method      :  DC_B_Init (component PWM)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT

/* END DC_B. */

#endif /* ifndef __DC_B */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
