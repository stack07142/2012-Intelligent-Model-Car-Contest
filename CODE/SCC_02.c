/** ###################################################################
**     Filename  : SCC_02.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Version   : Driver 01.14
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-02, ¿ÀÈÄ 6:30
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE SCC_02 */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
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
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdio.h>
#include "LCD.h"
#include "SevenSEG.h"
#include "PID.h"


#pragma DATA_SEG DEFAULT

word control_cnt = 0xFFFFU;
word control_cnt2 = 0xFFFFU;
byte adconv_cnt = 0xFFU;
word Measure_Values[8U] = {
 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U
};
word Adconv_Low_Max[8U] = {
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U
};
word Adconv_Low_Min[8U] = {
  0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU
};
word Adconv_Low_Delta[8U] = {
  0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU
};
word Adconv_Low[8U] = {
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U
};
int16_t Low_Weight[8U] = {
  -525, -360, -150, -24, 24, 150, 360, 525
};
int16_t line_pos = 0;
int16_t line_pos_hist[5] = {
  0, 0, 0, 0, 0
};
int32_t encoder_value = 0xFFFFU;
uint32_t encoder_F_value = 0xFFFFU;
uint32_t encoder_B_value = 0xFFFFU;
int16_t ratio_value = 0;
int16_t target_DC = 0;

byte fl_mode = 0x00U;
byte fl_run = 0x00U;

SPID Servo_pid;
SPID DC_pid;
SPID Distance_pid;

int16_t tmp = 1400;
int32_t tmp2 = 0;
// hitec
word servo_center = 1400;
word servo_left_max = 820;
word servo_right_max = 1980;

// sanwa
//word servo_center = 1475;
//word servo_left_max = 970;
//word servo_right_max = 1980;

// Park's values
#pragma CONST_SEG DEFAULT
const int16_t Max_Speed = 4500;

#pragma DATA_SEG DEFAULT
int16_t Target_Speed = 6000;


int16_t sum = 0;
int32_t weighted_sum = 0;
int16_t line_avg = 0;
int16_t line_pre_avg = 0;
int16_t last_value = 0;

// UltraSonic values
word echo_cnt = 0U;
byte fl_echo_cnt[3] = {
  0U, 0U, 0U
};

word US_cnt = 1U;
float US_distance[3U] = {
  0.0, 0.0, 0.0 
};
float US_distance_hist[3U][5U];
float US_distance_avg[3U] = {
  0.0, 0.0, 0.0
};
float tmp_US_max = 0;
float tmp_US_min = 0;


// Distance values
float distance = 75.0;
float target_distance = 15;
word break_value = 2400;
float break_distance = 13;


// sy...
float dist_moved = 0;



#pragma CONST_SEG DEFAULT

const byte Adconv_Table[8U] = {   /* Table of mask constants */
   0x03U, 0x04U, 0x02U, 0x05U, 0x01U, 0x06U, 0x00U, 0x07U
};

#pragma CODE_SEG DEFAULT

void main(void)
{
  /* Write your local variable definition here */
  byte k;
  byte disp_str[17U];
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  Cpu_DisableInt();
  Control_Timer_DisableEvent();
  DC_B_SetRatio8(0x00U);
  DC_F_SetRatio8(0x00U);
  Servo_SetDutyUS(servo_center);

  ExtInt_Rising_Disable();
  ExtInt_Falling_Disable();

  while(!(IR_Emitter_SetDutyUS(15)) == ERR_OK);
  while(!(ADConv_Disable() == ERR_OK));
  ADConv_DisableEvent();
  US_echo_timer_DisableEvent();

  initLCD();
  US_distance_hist[0][0] = 0.0;
  US_distance_hist[0][1] = 0.0;
  US_distance_hist[0][2] = 0.0;
  US_distance_hist[0][3] = 0.0;
  US_distance_hist[0][4] = 0.0;
  
  US_distance_hist[1][0] = 0.0;
  US_distance_hist[1][1] = 0.0;
  US_distance_hist[1][2] = 0.0;
  US_distance_hist[1][3] = 0.0;
  US_distance_hist[1][4] = 0.0;
  
  US_distance_hist[2][0] = 0.0;
  US_distance_hist[2][1] = 0.0;
  US_distance_hist[2][2] = 0.0;
  US_distance_hist[2][3] = 0.0;
  US_distance_hist[2][4] = 0.0;  
 
 
  LEDs_SetBit(4);
  Cpu_Delay100US(30000);
  LEDs_PutVal(0x00U);
  
  sprintf(disp_str, "Team MIE SCC\0");
  stringDisp(disp_str, 0);
  
  SevenSEG_Data_PutVal(NumToSeg(1));
  SevenSEG_Signal_PutVal(~0x01);
  while(!Switchs_GetBit(3));
  Cpu_Delay100US(2000);
  SevenSEG_Signal_PutVal(0x0FU);
  LEDs_NegBit(3);
  
  
  while(!(Switchs_GetBit(3)))
  {
    if(Switchs_GetBit(0)) 
    {
      //Servo_SetDutyUS(2000);
      servo_center = servo_center + 5;
      Cpu_Delay100US(2000);
    }
      
    if(Switchs_GetBit(1))
    {
      //Servo_SetDutyUS(1000);
      servo_center = servo_center - 5;
      Cpu_Delay100US(2000);
    }
    
    if(Switchs_GetBit(2)) 
    {
      //Servo_SetDutyUS(1500);
      servo_center = 1575;
      Cpu_Delay100US(2000);
    }

    Servo_SetDutyUS(servo_center);
    
    // print segment
    
    SevenSEG_Data_PutVal(NumToSeg(servo_center%10));
    SevenSEG_Signal_PutVal(~0x01);
    Cpu_Delay100US(10); //1ms
    SevenSEG_Signal_PutVal(0x0FU);
    
    SevenSEG_Data_PutVal(NumToSeg((servo_center/10)%10));
    SevenSEG_Signal_PutVal(~0x02);
    Cpu_Delay100US(10); //1ms
    SevenSEG_Signal_PutVal(0x0FU);

    SevenSEG_Data_PutVal(NumToSeg((servo_center/100)%10));
    SevenSEG_Signal_PutVal(~0x04);
    Cpu_Delay100US(10); //1ms
    SevenSEG_Signal_PutVal(0x0FU);    
  
    SevenSEG_Data_PutVal(NumToSeg((servo_center/1000)%10));
    SevenSEG_Signal_PutVal(~0x08);
    Cpu_Delay100US(10); //1ms
    SevenSEG_Signal_PutVal(0x0FU);   
    
    
    
  }
  //servo_center = 1585;
  Servo_SetDutyUS(servo_center);
  Cpu_Delay100US(2000);
  LEDs_NegBit(3);
  
  SevenSEG_Data_PutVal(NumToSeg(2));
  SevenSEG_Signal_PutVal(~0x01);
  Cpu_Delay100US(10000);

  
  DC_Direction_F_ClrVal();
  DC_Direction_B_ClrVal();
  
  LEDs_NegBit(3);
  while(!Switchs_GetBit(3))
  {
    if(Switchs_GetBit(0))
    {
      LEDs_NegBit(1);
      ratio_value = ratio_value + 10;
      Cpu_Delay100US(2000);
    }
    if(Switchs_GetBit(1))
    {
      LEDs_NegBit(2);
      ratio_value = ratio_value - 10;
      Cpu_Delay100US(2000);
    }
    
    if(ratio_value > 240)  ratio_value = 240;
    if(ratio_value < -240) ratio_value = -240;
    
    if(ratio_value >= 0)
    {
      LEDs_ClrBit(0);
      DC_Direction_F_SetVal();
      DC_Direction_B_ClrVal();
      DC_F_SetRatio8((byte)ratio_value);     
      DC_B_SetRatio8(0x00U);
    }
    else
    {
      LEDs_SetBit(0);
      DC_Direction_F_ClrVal();
      DC_Direction_B_SetVal();
      DC_F_SetRatio8(0x00U);
      DC_B_SetRatio8((byte)(ratio_value*(-1)));
    }

  }
  LEDs_NegBit(3);
  DC_Direction_F_ClrVal();
  DC_Direction_B_ClrVal();
  LEDs_PutVal(0x00U);

  Cpu_Delay100US(10000);
  
  InitSPID(&Servo_pid);
  InitSPID(&DC_pid);
  InitSPID(&Distance_pid);
  fl_mode = 0x00U;
  
  Target_Speed = 0;
  /*******  SERVO  *******/  
  SetGain(&Servo_pid, 1.1, 0.001311, 8.54);
 
  /*******    DC    *******/
  SetGain(&DC_pid, 30, 0.002, 1.0);
  
  /******* DISTANCE *******/
  SetGain(&Distance_pid, 15, 0.01, 800);
  
  Set_iMinMax(&Distance_pid, -60000, 60000);

  Set_iMinMax(&DC_pid, -60000, 60000);


  
  stringDisp("Find Adconv Max \0", 0);
  stringDisp("Values Ing......\0", 1);
  
  
  SevenSEG_Signal_PutVal(0x0FU);   
  SevenSEG_Data_PutVal(NumToSeg(3));
  SevenSEG_Signal_PutVal(~0x01);  
 
 
  while(!(ADConv_Enable() == ERR_OK));
  fl_mode = 1U;
  fl_run = 0x00U;             
  adconv_cnt = 0x00U;
  ADConv_EnableEvent();
  Control_Timer_EnableEvent();
  Encoder_F_ResetCounter();
  Encoder_B_ResetCounter();
  encoder_value = 0x0000U;
  encoder_F_value = 0x0000U;
  encoder_B_value = 0x0000U;
  
  Cpu_EnableInt();
  LEDs_NegBit(3);

  while(!Switchs_GetBit(3));
  LEDs_NegBit(3);
  SevenSEG_Signal_PutVal(~0x03);
  Cpu_Delay100US(1500);
  // disable all interrupts
  Cpu_DisableInt();
  Control_Timer_DisableEvent();
  ExtInt_Rising_Disable();
  ExtInt_Falling_Disable();
  ADConv_DisableEvent();
  US_echo_timer_DisableEvent();
  
  while(!Switchs_GetBit(3))
  {
    // print Max Values
    sprintf(disp_str, "%4u%4u%4u%4u\0", Adconv_Low_Max[0], Adconv_Low_Max[1], Adconv_Low_Max[2], Adconv_Low_Max[3]);
    stringDisp(disp_str, 0);
    Cpu_Delay100US(10);  // 1ms
    sprintf(disp_str, "%4u%4u%4u%4u\0", Adconv_Low_Max[4], Adconv_Low_Max[5], Adconv_Low_Max[6], Adconv_Low_Max[7]);
    stringDisp(disp_str, 1);
    Cpu_Delay100US(10);  // 1ms
  }
  instructionSet(0x01U);
  Cpu_Delay100US(10000);
  LEDs_NegBit(3);
  SevenSEG_Signal_PutVal(0x0FU);   
  SevenSEG_Data_PutVal(NumToSeg(4));
  SevenSEG_Signal_PutVal(~0x01);  
  fl_mode = 2;

  stringDisp("Find Adconv Min \0", 0);
  stringDisp("values ing......\0", 1);
  // enable all interrupts
  adconv_cnt = 0x00U;
  ADConv_EnableEvent();
  ExtInt_Rising_Enable();
  ExtInt_Falling_Enable();
  Control_Timer_EnableEvent();
  Cpu_EnableInt();
  
  
  while(!Switchs_GetBit(3));
  LEDs_NegBit(3);
  
  SevenSEG_Signal_PutVal(~0x03);
  Cpu_Delay100US(1500);
  // disable all interrupts
  Cpu_DisableInt();
  Control_Timer_DisableEvent();
  ExtInt_Rising_Disable();
  ExtInt_Falling_Disable();
  ADConv_DisableEvent();
  US_echo_timer_DisableEvent();
  
  while(!Switchs_GetBit(3))
  {
    // print min Values
    sprintf(disp_str, "%4u%4u%4u%4u\0", Adconv_Low_Min[0], Adconv_Low_Min[1], Adconv_Low_Min[2], Adconv_Low_Min[3]);
    stringDisp(disp_str, 0);
    Cpu_Delay100US(10);  // 1ms
    sprintf(disp_str, "%4u%4u%4u%4u\0", Adconv_Low_Min[4], Adconv_Low_Min[5], Adconv_Low_Min[6], Adconv_Low_Min[7]);
    stringDisp(disp_str, 1);
    Cpu_Delay100US(10);  // 1ms
  }
  instructionSet(0x01U);
  
  Cpu_Delay100US(10000);
  LEDs_NegBit(3);
  SevenSEG_Signal_PutVal(0x0FU);   
  SevenSEG_Data_PutVal(NumToSeg(5));
  SevenSEG_Signal_PutVal(~0x01); 
  
  // Adconv_Low_Min & Max values 5% cut!
  for(k=0; k<8U; k++)
  {
    Adconv_Low_Max[k] = 0.95 * Adconv_Low_Max[k];
    //Adconv_Low_Min[k] = 0.05 * Adconv_Low_Delta[k];
    Adconv_Low_Delta[k] = Adconv_Low_Max[k] - Adconv_Low_Min[k];
  }
  SevenSEG_Signal_PutVal(~0x03);
  stringDisp("Ready!\0",0);
  stringDisp("Press SW3 -> Go!\0",1);  
  
  fl_mode = 3;
  control_cnt = 0;
    // enable all interrupts
  adconv_cnt = 0x00U;
  ADConv_EnableEvent();
  ExtInt_Rising_Enable();
  ExtInt_Falling_Enable();
  Control_Timer_EnableEvent();
  Cpu_EnableInt();

  
  while(!Switchs_GetBit(3));
  LEDs_NegBit(3);
  Cpu_Delay100US(10000);
  LEDs_NegBit(3);
  SevenSEG_Signal_PutVal(0x0FU);   
  SevenSEG_Data_PutVal(NumToSeg(6));
  SevenSEG_Signal_PutVal(~0x01);
  Flush_iState(&Servo_pid);
  Flush_iState(&Distance_pid);
  Flush_iState(&DC_pid);
  fl_run = 0x01U;
  control_cnt = 0;
    
  
  
  while(1)
  {
    if(fl_mode == 0xFFU) {
    // print segment
    
    SevenSEG_Data_PutVal(NumToSeg(last_value%10));
    SevenSEG_Signal_PutVal(~0x01);
    Cpu_Delay100US(10); //1ms
    SevenSEG_Signal_PutVal(0x0FU);
    
    SevenSEG_Data_PutVal(NumToSeg((last_value/10)%10));
    SevenSEG_Signal_PutVal(~0x02);
    Cpu_Delay100US(10); //1ms
    SevenSEG_Signal_PutVal(0x0FU);

    SevenSEG_Data_PutVal(NumToSeg((last_value/100)%10));
    SevenSEG_Signal_PutVal(~0x04);
    Cpu_Delay100US(10); //1ms
    SevenSEG_Signal_PutVal(0x0FU);    
  
    SevenSEG_Data_PutVal(NumToSeg((last_value/1000)%10));
    SevenSEG_Signal_PutVal(~0x08);
    Cpu_Delay100US(10); //1ms
    SevenSEG_Signal_PutVal(0x0FU); 
    }
      
  }
  

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END SCC_02 */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
