/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : ADConv.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : ADC
**     Version   : Component 01.593, Driver 01.18, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings  :
**         AD control register         : ATD0CTL4    [$02C4]
**         Interrupt name              : Vatd0
**         Interrupt enable reg.       : ATD0CTL23   [$02C2]
**         Priority                    : 4
**         User handling procedure     : ADConv_OnEnd
**         Number of conversions       : 1
**         AD resolution               : 12-bit
**
**         Input pins
**
**              Port name              : AD0L
**              Bit number (in port)   : 0
**              Bit mask of the port   : $0001
**              Port data register     : PT1AD0      [$0271]
**              Port control register  : DDR1AD0     [$0273]
**
**              Port name              : AD0L
**              Bit number (in port)   : 1
**              Bit mask of the port   : $0002
**              Port data register     : PT1AD0      [$0271]
**              Port control register  : DDR1AD0     [$0273]
**
**              Port name              : AD0L
**              Bit number (in port)   : 2
**              Bit mask of the port   : $0004
**              Port data register     : PT1AD0      [$0271]
**              Port control register  : DDR1AD0     [$0273]
**
**              Port name              : AD0L
**              Bit number (in port)   : 3
**              Bit mask of the port   : $0008
**              Port data register     : PT1AD0      [$0271]
**              Port control register  : DDR1AD0     [$0273]
**
**              Port name              : AD0L
**              Bit number (in port)   : 4
**              Bit mask of the port   : $0010
**              Port data register     : PT1AD0      [$0271]
**              Port control register  : DDR1AD0     [$0273]
**
**              Port name              : AD0L
**              Bit number (in port)   : 5
**              Bit mask of the port   : $0020
**              Port data register     : PT1AD0      [$0271]
**              Port control register  : DDR1AD0     [$0273]
**
**              Port name              : AD0L
**              Bit number (in port)   : 6
**              Bit mask of the port   : $0040
**              Port data register     : PT1AD0      [$0271]
**              Port control register  : DDR1AD0     [$0273]
**
**              Port name              : AD0L
**              Bit number (in port)   : 7
**              Bit mask of the port   : $0080
**              Port data register     : PT1AD0      [$0271]
**              Port control register  : DDR1AD0     [$0273]
**
**         Initialization:
**              Conversion             : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-20
**     Contents  :
**         Enable             - byte ADConv_Enable(void);
**         Disable            - byte ADConv_Disable(void);
**         EnableEvent        - byte ADConv_EnableEvent(void);
**         DisableEvent       - byte ADConv_DisableEvent(void);
**         MeasureChanNotWait - byte ADConv_MeasureChanNotWait(byte Channel);
**         GetChanValue8      - byte ADConv_GetChanValue8(byte Channel, byte *Value);
**         GetChanValue16     - byte ADConv_GetChanValue16(byte Channel, word *Value);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/


/* MODULE ADConv. */

#pragma MESSAGE DISABLE C5703          /* Disable warning C5703 "Parameter is not referenced" */
#pragma MESSAGE DISABLE C4002          /* Disable warning C4002 "Result not used is ignored" */
#pragma MESSAGE DISABLE C12056         /* Disable warning C12056 "SP debug info incorrect because of optimization or inline assembler" */

#include "Events.h"
#include "ADConv.h"

#pragma DATA_SEG ADConv_DATA           /* Select data segment "ADConv_DATA" */
#pragma CODE_SEG ADConv_CODE
#pragma CONST_SEG ADConv_CONST         /* Constant section for this module */

#define STOP            0U             /* STOP state           */
#define MEASURE         1U             /* MESURE state         */
#define CONTINUOUS      2U             /* CONTINUOUS state      */
#define SINGLE          3U             /* SINGLE state         */

static const byte Table[] = {          /* Table of mask constants */
0x01U,0x02U,0x04U,0x08U,0x10U,0x20U,0x40U,0x80U};
static const byte Channels[] = {       /* Contents for the device control register */
0x00U,0x01U,0x02U,0x03U,0x04U,0x05U,0x06U,0x07U};
static bool EnUser;                    /* Enable/Disable device */
volatile bool ADConv_EnEvent;          /* Enable/Disable events */
static byte OutFlg;                    /* Measurement finish flag */
static byte SumChan;                   /* Number of measured channels */
volatile static byte ModeFlg;          /* Current state of device */
static word ADConv_OutV[8];            /* Array of measured values */
/*
** ===================================================================
**     Method      :  ADConv_Interrupt (component ADC)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(ADConv_Interrupt)
{
  ADConv_OutV[SumChan] = ATD0DR0;      /* Save measured value */
  OutFlg |= Table[SumChan];            /* Value of measured channel is available */
  if (ADConv_EnEvent) {                /* Are events enables? */
    ADConv_OnEnd();                    /* Invoke user event */
  }
  ModeFlg = STOP;                      /* Set the device to the stop mode */
}

#pragma CODE_SEG ADConv_CODE
/*
** ===================================================================
**     Method      :  HWEnDi (component ADC)
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
    if (ModeFlg) {                     /* Start or stop measurement? */
      OutFlg &= (byte)(~(byte)Table[SumChan]); /* Output value isn't available */
      ATD0CTL5 = Channels[SumChan];    /* Start the conversion */
    }
    else {
      /* ATD0CTL3: DJM=0,S8C=0,S4C=0,S2C=0,S1C=1,FIFO=0,FRZ1=0,FRZ0=0 */
      ATD0CTL3 = 0x08U;                /* Abort current measurement */
    }
  }
}

/*
** ===================================================================
**     Method      :  ADConv_Enable (component ADC)
**
**     Description :
**         Enables A/D converter component. <Events> may be generated
**         (<DisableEvent>/<EnableEvent>). If possible, this method
**         switches on A/D converter device, voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte ADConv_Enable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    return ERR_OK;                     /* If yes then set the flag "device enabled" */
  }
  EnUser = TRUE;                       /* Set the flag "device enabled" */
  HWEnDi();                            /* Enable the device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADConv_Disable (component ADC)
**
**     Description :
**         Disables A/D converter component. No <events> will be generated.
**         If possible, this method switches off A/D converter device,
**         voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte ADConv_Disable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return ERR_OK;                     /* If yes then OK */
  }
  EnUser = FALSE;                      /* If yes then set the flag "device disabled" */
  HWEnDi();                            /* Enable the device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADConv_EnableEvent (component ADC)
**
**     Description :
**         Enables the <events>.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte ADConv_EnableEvent(void)

**  This method is implemented as a macro. See ADConv.h file.  **
*/
/*
** ===================================================================
**     Method      :  ADConv_DisableEvent (component ADC)
**
**     Description :
**         Disables the <events>.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte ADConv_DisableEvent(void)

**  This method is implemented as a macro. See ADConv.h file.  **
*/
/*
** ===================================================================
**     Method      :  ADConv_MeasureChanNotWait (component ADC)
**
**     Description :
**         This method performs one measurement from one channel and
**         doesn't wait till the end of the measurement. (Note: If the
**         <number of conversions> is more than one the conversion of
**         A/D channels is performed specified number of times.)
**     Parameters  :
**         NAME            - DESCRIPTION
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored, because the parameter
**                           is set inside this method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
**                           ERR_RANGE - Parameter "Channel" out of range
** ===================================================================
*/
byte ADConv_MeasureChanNotWait(byte Channel)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  if (Channel >= 8U) {                 /* Is channel number greater than or equal to 8 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = SINGLE;                    /* Set state of device to the measure mode */
  SumChan = Channel;                   /* Set required channel */
  HWEnDi();                            /* Start measurement */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADConv_GetChanValue8 (component ADC)
**
**     Description :
**         This method returns the last measured value of required
**         channel justified to the left. Compared with <GetChanValue>
**         method this method returns more accurate result if the
**         <number of conversions> is greater than 1 and <AD resolution>
**         is less than 8 bits. In addition, the user code dependency
**         on <AD resolution> is eliminated.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored.
**       * Value           - Pointer to the measured value.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
** ===================================================================
*/
byte ADConv_GetChanValue8(byte Channel,byte *Value)
{
  if (Channel >= 8U) {                 /* Is channel number greater than or equal to 8 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if ((OutFlg & Table[Channel]) == 0U) { /* Is measured value(s) available? */
    return ERR_NOTAVAIL;
  }
  *Value = (byte)(ADConv_OutV[Channel] >> 8U); /* Save measured values to the output buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADConv_GetChanValue16 (component ADC)
**
**     Description :
**         This method returns the last measured value of the required
**         channel justified to the left. Compared with <GetChanValue>
**         method this method returns more accurate result if the
**         <number of conversions> is greater than 1 and <AD resolution>
**         is less than 16 bits. In addition, the user code dependency
**         on <AD resolution> is eliminated.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored.
**       * Value           - Pointer to the measured value.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
** ===================================================================
*/
byte ADConv_GetChanValue16(byte Channel,word *Value)
{
  if (Channel >= 8U) {                 /* Is channel number greater than or equal to 8 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if ((OutFlg & Table[Channel]) == 0U) { /* Is measured value(s) available? */
    return ERR_NOTAVAIL;
  }
  *Value = ADConv_OutV[Channel];       /* Save measured values to the output buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADConv_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ADConv_Init(void)
{
  EnUser = TRUE;                       /* Enable device */
  ADConv_EnEvent = TRUE;               /* Enable events */
  OutFlg = 0U;                         /* No measured value */
  ModeFlg = STOP;                      /* Device isn't running */
  /* ATD0CTL4: SMP2=1,SMP1=1,SMP0=1,PRS4=0,PRS3=1,PRS2=0,PRS1=0,PRS0=1 */
  ATD0CTL4 = 0xE9U;                    /* Set sample time and prescaler */
  /* ATD0CTL3: DJM=0,S8C=0,S4C=0,S2C=0,S1C=1,FIFO=0,FRZ1=0,FRZ0=0 */
  ATD0CTL3 = 0x08U;                    /* Set ATD control register 3 */
  /* ATD0CTL0: ??=0,??=0,??=0,??=0,WRAP3=1,WRAP2=1,WRAP1=1,WRAP0=1 */
  ATD0CTL0 = 0x0FU;                    /* Set wrap around */
  /* ATD0CTL1: ETRIGSEL=0,SRES1=1,SRES0=0,SMP_DIS=1,ETRIGCH3=1,ETRIGCH2=1,ETRIGCH1=1,ETRIGCH0=1 */
  ATD0CTL1 = 0x5FU;                    /* Set resolution and discharge */
  /* ATD0CTL2: ??=0,AFFC=1,ICLKSTP=0,ETRIGLE=0,ETRIGP=0,ETRIGE=0,ASCIE=1,ACMPIE=0 */
  ATD0CTL2 = 0x42U;                    /* Set ATD control register 2 */
}


/* END ADConv. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
