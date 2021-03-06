/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : IR_Emitter.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : PWM
**     Version   : Component 02.231, Driver 01.16, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-16, ���� 12:39
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


/* MODULE IR_Emitter. */

#include "IR_Emitter.h"

#pragma DATA_SEG IR_Emitter_DATA       /* Select data segment "IR_Emitter_DATA" */

#pragma CODE_SEG IR_Emitter_CODE

static bool EnUser;                    /* Enable/Disable device by user */
static word RatioStore;                /* Ratio of L-level to H-level */


/*
** ===================================================================
**     Method      :  HWEnDi (component PWM)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (EnUser) {                        /* Enable device? */
    PWME_PWME0 = 1U;                   /* Run counter */
  } else {                             /* Disable device? */
    PWME_PWME0 = 0U;                   /* Stop counter */
    PWMCNT0 = 0U;                      /* Reset counter */
  }
}

/*
** ===================================================================
**     Method      :  SetRatio (component PWM)
**
**     Description :
**         The method reconfigures the compare and modulo registers of 
**         the peripheral(s) when the speed mode changes. The method is 
**         called automatically as a part of the component 
**         SetHigh/SetLow/SetSlow methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma MESSAGE DISABLE C12056         /* Disable WARNING C12056: SP debug info incorrect because of optimization */
static void SetRatio(void)
{
  PWMDTY0 = (byte)(((0xFFUL * (dword)RatioStore) + 0x8000UL) >> 0x10U); /* Calculate new value according to the given ratio */
}
#pragma MESSAGE DEFAULT C12056         /* Re-enable WARNING C12056 */

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
byte IR_Emitter_Enable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    HWEnDi();                          /* Enable the device */
  }
  return ERR_OK;                       /* OK */
}

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
byte IR_Emitter_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    HWEnDi();                          /* Disable the device */
  }
  return ERR_OK;                       /* OK */
}

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
byte IR_Emitter_SetRatio8(byte Ratio)
{
  RatioStore = (((word)Ratio << 8U) + 0x80U); /* Store new value of the ratio */
  SetRatio();                          /* Calculate and set up new appropriate values of the duty and period registers */
  return ERR_OK;                       /* OK */
}

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
byte IR_Emitter_SetDutyUS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */

  if (Time > 0x80U) {                  /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Time, (dword)33686018, &rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi2(rtval[0], rtval[1], &RatioStore)) { /* Is the result greater or equal than 65536 ? */
    RatioStore = 0xFFFFU;              /* If yes then use maximal possible value */
  }
  SetRatio();                          /* Calculate and set up new appropriate values of the duty and period registers */
  return ERR_OK;                       /* OK */
}

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
byte IR_Emitter_SetValue(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    return ERR_ENABLED;                /* If yes then error */
  }
  PWMPOL_PPOL0 = 1U;                   /* Set output signal level to high */
  PTP_PTP0 = 1U;
  return ERR_OK;                       /* OK */
}

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
byte IR_Emitter_ClrValue(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    return ERR_ENABLED;                /* If yes then error */
  }
  PWMPOL_PPOL0 = 0U;                   /* Set output signal level to low */
  PTP_PTP0 = 0U;
  return ERR_OK;                       /* OK */
}

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
void IR_Emitter_Init(void)
{
  /* PWMCNT0: PWMCNT0=0 */
  setReg8(PWMCNT0, 0x00U);             /* Reset Counter */ 
  /* PWMSDN: PWMIF=1,PWMIE=0,PWMRSTRT=0,PWMLVL=0,??=0,PWM7IN=0,PWM7INL=0,PWM7ENA=0 */
  setReg8(PWMSDN, 0x80U);              /* Emergency shutdown feature settings */ 
  RatioStore = 0x0F0FU;                /* Store initial value of the ratio */
  EnUser = TRUE;                       /* Enable device */
  /* PWMDTY0: PWMDTY0=0x0F */
  setReg8(PWMDTY0, 0x0FU);             /* Store initial value to the duty-compare register */ 
  /* PWMPER0: PWMPER0=0xFF */
  setReg8(PWMPER0, 0xFFU);             /* and to the period register */ 
  /* PWMPRCLK: ??=0,PCKB2=0,PCKB1=0,PCKB0=0,??=0,PCKA2=0,PCKA1=1,PCKA0=1 */
  setReg8(PWMPRCLK, 0x03U);            /* Set prescaler register */ 
  /* PWMSCLA: BIT7=0,BIT6=0,BIT5=1,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  setReg8(PWMSCLA, 0x20U);             /* Set scale register */ 
  /* PWMCLK: PCLK0=0 */
  clrReg8Bits(PWMCLK, 0x01U);          /* Select clock source */ 
  HWEnDi();                            /* Enable/disable device according to status flags */
}

/* END IR_Emitter. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
