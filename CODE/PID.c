/** ###################################################################
**     Filename  : PID.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-04, ¿ÀÈÄ 10:18
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE PID */
#include "PID.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"
#include "LEDs.h"

#pragma DATA_SEG PID_DATA /* Select data segment "PID_DATA" */
#pragma CODE_SEG PID_CODE
#pragma CONST_SEG PID_CONST /* Constant section for this module */

#pragma CODE_SEG PID_CODE

int32_t UpdatePID(SPID *pid, int32_t error, int32_t position)
{
  float pTerm, iTerm, dTerm;
  
  pTerm = pid->pGain * error; // calculate the proportional term
    
  // calculate the integral state with appropriate limiting
  if(error > 0)
  {
    if(!pid->error_state)  Flush_iState(pid);
    pid->error_state = 0x01U;
  }
  else if(error < 0)
  {
    if(pid->error_state) Flush_iState(pid);
    pid->error_state = 0x00U;
  }
  else
  {
    Flush_iState(pid);  
  }

  
  pid->iState += error;
     
  if(pid->iState > pid->iMax) 
  {
    pid->iState = pid->iMax;
  }
  else if(pid->iState < pid->iMin) 
  {
    pid->iState = pid->iMin;
  }
  
  // calculate the integral term
  iTerm = pid->iGain * pid->iState;
  
  // calculate the derivative term
  dTerm = pid->dGain * (position - pid->dState);
  pid->dState = position;
  
  // return the sum of p, i, d terms.
  return (int32_t) (pTerm + iTerm + dTerm);
}

float UpdatePID_float(SPID *pid, float error, float position)
{
  float pTerm, iTerm, dTerm;
  
  pTerm = pid->pGain * error; // calculate the proportional term
    
  // calculate the integral state with appropriate limiting
  if(error > 0)
  {
    if(!pid->error_state)  Flush_iState(pid);
    pid->error_state = 0x01U;
  }
  else if(error < 0)
  {
    if(pid->error_state) Flush_iState(pid);
    pid->error_state = 0x00U;
  }
  else
  {
    Flush_iState(pid);  
  } 
  
  pid->iState += error;   
  if(pid->iState > pid->iMax) 
  {
    pid->iState = pid->iMax;
  }
  else if(pid->iState < pid->iMin) 
  {
    pid->iState = pid->iMin;
  }
  
  // calculate the integral term
  iTerm = pid->iGain * pid->iState;
  
  // calculate the derivative term
  dTerm = pid->dGain * (position - pid->dState);
  pid->dState = position;
  
  // return the sum of p, i, d terms.
  return (float) (pTerm + iTerm + dTerm);
}


void SetGain(SPID *pid, float Kp, float Ki, float Kd)
{
  pid->pGain = Kp;
  pid->iGain = Ki;
  pid->dGain = Kd;
}

void InitSPID(SPID *pid)
{
  pid->dState = 0;
  pid->iState = 0;
  Set_iMinMax(pid, 0, 0);
  
  SetGain(pid, 0.0, 0.0, 0.0);
  
  pid->error_state = 0x01U;
}

void Flush_iState(SPID *pid)
{
  pid->iState = 0;
  LEDs_NegBit(4);

}
  
void Set_iMinMax(SPID *pid, float imin, float imax)
{
  pid->iMin = imin;
  pid->iMax = imax;
}



/* END PID */
