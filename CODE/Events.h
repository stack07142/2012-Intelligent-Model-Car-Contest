/** ###################################################################
**     Filename  : Events.h
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : Events
**     Version   : Driver 01.04
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-02, ¿ÀÈÄ 6:30
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "LEDs.h"
#include "Switchs.h"
#include "ExtInt_Rising.h"
#include "ExtInt_Falling.h"
#include "IR_Emitter.h"
#include "ADConv.h"
#include "Control_Timer.h"
#include "Encoder_F.h"
#include "DC_F.h"
#include "DC_B.h"
#include "Servo.h"
#include "Encoder_Direction.h"
#include "DC_Direction_F.h"
#include "DC_Direction_B.h"
#include "LCDport.h"
#include "SevenSEG_Data.h"
#include "SevenSEG_Signal.h"
#include "US_echo_timer.h"
#include "US0_echo.h"
#include "US0_trigger.h"
#include "US1_echo.h"
#include "US1_trigger.h"
#include "Encoder_B.h"
#include "US2_echo.h"
#include "US2_trigger.h"

#pragma CODE_SEG DEFAULT


void ExtInt_Falling_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  ExtInt_Falling_OnInterrupt (module Events)
**
**     Component   :  ExtInt_Falling [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ExtInt_Rising_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  ExtInt_Rising_OnInterrupt (module Events)
**
**     Component   :  ExtInt_Rising [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ADConv_OnEnd(void);
/*
** ===================================================================
**     Event       :  ADConv_OnEnd (module Events)
**
**     Component   :  ADConv [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Control_Timer_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  Control_Timer_OnInterrupt (module Events)
**
**     Component   :  Control_Timer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void US_echo_timer_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  US_echo_timer_OnInterrupt (module Events)
**
**     From bean   :  US_echo_timer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the bean is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
