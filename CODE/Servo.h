/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Servo.h
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
**                       3             |  PP1_KWP1_PWM1_MOSI1_TIMIOC1
**             ----------------------------------------------------
**
**         Timer name                  : PWM1 [8-bit]
**         Counter                     : PWMCNT1   [$030D]
**         Mode register               : PWMCTL    [$0305]
**         Run register                : PWME      [$0300]
**         Prescaler                   : PWMPRCLK  [$0303]
**         Compare 1 register          : PWMPER1   [$0315]
**         Compare 2 register          : PWMDTY1   [$031D]
**         Flip-flop 1 register        : PWMPOL    [$0301]
**
**         User handling procedure     : not specified
**
**         Output pin
**
**         Port name                   : P
**         Bit number (in port)        : 1
**         Bit mask of the port        : $0002
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
**         Enable    - byte Servo_Enable(void);
**         Disable   - byte Servo_Disable(void);
**         SetDutyUS - byte Servo_SetDutyUS(word Time);
**         SetValue  - byte Servo_SetValue(void);
**         ClrValue  - byte Servo_ClrValue(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __Servo
#define __Servo

/* MODULE Servo. */

#include "Cpu.h"

#pragma CODE_SEG Servo_CODE

#define Servo_PERIOD_VALUE   0xFAUL    /* Initial period value in ticks of the timer */
#define Servo_PERIOD_VALUE_HIGH 0xFAUL /* Initial period value in ticks of the timer in high speed mode */

byte Servo_Enable(void);
/*
** ===================================================================
**     Method      :  Servo_Enable (component PWM)
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

byte Servo_Disable(void);
/*
** ===================================================================
**     Method      :  Servo_Disable (component PWM)
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

byte Servo_SetDutyUS(word Time);
/*
** ===================================================================
**     Method      :  Servo_SetDutyUS (component PWM)
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

byte Servo_SetValue(void);
/*
** ===================================================================
**     Method      :  Servo_SetValue (component PWM)
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

byte Servo_ClrValue(void);
/*
** ===================================================================
**     Method      :  Servo_ClrValue (component PWM)
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

void Servo_Init(void);
/*
** ===================================================================
**     Method      :  Servo_Init (component PWM)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT

/* END Servo. */

#endif /* ifndef __Servo */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
