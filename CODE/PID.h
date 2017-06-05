/** ###################################################################
**     Filename  : PID.h
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-04, ¿ÀÈÄ 10:18
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __PID_H
#define __PID_H

/* MODULE PID */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

#pragma DATA_SEG PID_DATA

typedef struct 
{
  float dState;
  float iState;
  float iMax;
  float iMin;
  
  float   pGain;
  float   iGain;
  float   dGain;
  
  byte    error_state;
} SPID;

#pragma CODE_SEG PID_CODE

int32_t UpdatePID(SPID *pid, int32_t error, int32_t position);

float UpdatePID_float(SPID *pid, float error, float position);

void SetGain(SPID *pid, float Kp, float Ki, float Kd);

void InitSPID(SPID *pid);

void Flush_iState(SPID *pid);

void Set_iMinMax(SPID *pid, float imin, float imax);

/* END PID */

#endif

