/** ###################################################################
**     Filename  : Events.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Component : Events
**     Version   : Driver 01.04
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-02, 오후 6:30
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "LCD.h"
#include "SevenSEG.h"
#include "PID.h"

extern word control_cnt;
extern word control_cnt2;
extern byte adconv_cnt;
extern word Measure_Values[8U];
extern word Adconv_Low_Max[8U];
extern word Adconv_Low_Min[8U];
extern word Adconv_Low_Delta[8U];
extern word Adconv_Low[8U];
extern int16_t Low_Weight[8U];
extern int16_t line_pos;
extern int16_t line_pos_hist[5];
extern int32_t encoder_value;
extern uint32_t encoder_F_value;
extern uint32_t encoder_B_value;
extern int16_t ratio_value;
extern int16_t target_DC;

extern byte fl_mode;
extern byte fl_run;

extern SPID Servo_pid;
extern SPID DC_pid;
extern SPID Distance_pid;

extern int16_t tmp;
extern int32_t tmp2;
extern word servo_center;
extern word servo_left_max;
extern word servo_right_max;


// Park's values
extern const int16_t Max_Speed;
extern int16_t Target_Speed;

// UltraSonic values

extern word echo_cnt;
extern byte fl_echo_cnt[3U];
extern word US_cnt;
extern float US_distance[3U];
extern float US_distance_hist[3U][5U];
extern float US_distance_avg[3U];
extern float tmp_US_max;
extern float tmp_US_min;

extern int16_t last_value;

// Distance values
extern float distance;
extern float target_distance;
extern word break_value;
extern float break_distance;

extern const byte Adconv_Table[8U];


extern int16_t sum;
extern int32_t weighted_sum;
extern int16_t line_avg;
extern int16_t line_pre_avg;

// sy..
extern float dist_moved;

static byte i, j=0;

#pragma CODE_SEG DEFAULT

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
void ExtInt_Falling_OnInterrupt(void)
{
  /* place your ExtInt_Falling interrupt procedure body here */
         ADConv_MeasureChanNotWait(Adconv_Table[adconv_cnt]);
}


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
void ExtInt_Rising_OnInterrupt(void)
{
  /* place your ExtInt_Rising interrupt procedure body here */
}


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
void ADConv_OnEnd(void)
{
  /* Write your code here ... */
  LEDs_SetBit(3);
  ADConv_GetChanValue16(Adconv_Table[adconv_cnt], &Measure_Values[Adconv_Table[adconv_cnt]]);
  Measure_Values[Adconv_Table[adconv_cnt]] = Measure_Values[Adconv_Table[adconv_cnt]] >> 4;
  
  adconv_cnt++;

  if(adconv_cnt > 0x07U)
  {
    adconv_cnt = 0x00U;
    ExtInt_Rising_Disable();
    ExtInt_Falling_Disable();
    ADConv_DisableEvent();

    // one-two
    // US_trigger on
    if(US_cnt)  US_cnt = 0U;
    else        US_cnt = 1U;
    
    if(US_cnt)// 1// == 0)
    {
      // 1. trigger
      US0_trigger_SetVal();
      US2_trigger_SetVal();
      Cpu_Delay100US(1); //trigger pulse delay
      US0_trigger_ClrVal();
      US2_trigger_ClrVal();
      Cpu_Delay100US(7); //sonic burst delay (8cm ~ 65cm)
      fl_echo_cnt[0] = 1U;
      fl_echo_cnt[2] = 1U;

    }
    else      //0  // if(US_cnt == 1)
    {
      // 1. trigger
      US1_trigger_SetVal();
      Cpu_Delay100US(1); //trigger pulse delay
      US1_trigger_ClrVal();
      Cpu_Delay100US(7); //sonic burst delay (8cm ~ 65cm)
    }

    echo_cnt = 0U;
    US_echo_timer_Enable();
    US_echo_timer_EnableEvent();    



    
    // 2. sonic burst    
   
  }
  LEDs_ClrBit(3);

}

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
void Control_Timer_OnInterrupt(void)
{
  /* Write your code here ... */
  //LEDs_SetBit(3);
  encoder_F_value = Encoder_F_GetCounterValue();
  Encoder_F_ResetCounter();
  encoder_B_value = Encoder_B_GetCounterValue();
  Encoder_B_ResetCounter();
  
  encoder_value = (int32_t) (encoder_F_value - encoder_B_value);
  
  control_cnt++;

  if(fl_mode == 1)     // renew max value
  {
    for(i=0; i<8; i++)
    {
      if(Measure_Values[i] > Adconv_Low_Max[i])
      {
        Adconv_Low_Max[i] = Measure_Values[i];
      }
    }
  }
  else if(fl_mode == 2) // renew min value & delta
  {
    for(i=0; i<8; i++)
    {
      if(Measure_Values[i] < Adconv_Low_Min[i])
      {
        Adconv_Low_Min[i] = Measure_Values[i];
      }
      Adconv_Low_Delta[i] = Adconv_Low_Max[i] - Adconv_Low_Min[i];      
    }  
  }
  else if(fl_mode == 3)
  {
    sum = 0;
    weighted_sum = 0;    
    for(i=0; i<8; i++)
    {
      if(Measure_Values[i] > Adconv_Low_Max[i]) Measure_Values[i] = Adconv_Low_Max[i];
      if(Measure_Values[i] < Adconv_Low_Min[i]) Measure_Values[i] = Adconv_Low_Min[i];
            
      Adconv_Low[i] = 100 * (Adconv_Low_Max[i] - Measure_Values[i]) / (Adconv_Low_Delta[i]);
      sum = sum + Adconv_Low[i];
      weighted_sum = weighted_sum + (int32_t)Adconv_Low[i] * Low_Weight[i];  
    }
    line_pos = weighted_sum/sum;
    line_pos_hist[0] = line_pos_hist[1];
    line_pos_hist[1] = line_pos_hist[2];
    line_pos_hist[2] = line_pos_hist[3];
    line_pos_hist[3] = line_pos_hist[4];
    line_pos_hist[4] = line_pos;
    
    line_pre_avg = line_avg;
    
    line_avg = (line_pos_hist[0] + line_pos_hist[1] + line_pos_hist[2] + line_pos_hist[3] + line_pos_hist[4]) / 5;
         
    if(sum < 70)
    {                     
      if(sum < 20)
      { 
        if(line_pre_avg < 0)  line_avg = -525;
        else if(line_pre_avg > 0) line_avg = 525;
      }
      else
      {
        if(Adconv_Low[7] >= 30)      line_avg = 525;
        else if(Adconv_Low[0] >= 30) line_avg = -525;
      }
    }
    
       
            
    tmp = servo_center + UpdatePID(&Servo_pid, (0 - line_avg), (0 - line_avg));
    
    if(tmp < 1200 || tmp > 1600)  Flush_iState(&Servo_pid);
                
    //if(tmp > 2100)      tmp = 2100;
    if(tmp > servo_right_max)      tmp = servo_right_max;
    else if(tmp < servo_left_max)  tmp = servo_left_max;
    
    
    for(i=0; i<3; i++) 
    {
      US_distance_hist[i][0] = US_distance_hist[i][1];
      US_distance_hist[i][1] = US_distance_hist[i][2];
      US_distance_hist[i][2] = US_distance_hist[i][3];
      US_distance_hist[i][3] = US_distance_hist[i][4];
      US_distance_hist[i][4] = US_distance[i];
      tmp_US_max = 7;
      tmp_US_min = 80;
      for(j=0; j<5; j++) 
      {
        if(US_distance_hist[i][j] > tmp_US_max) tmp_US_max = US_distance_hist[i][j];
        if(US_distance_hist[i][j] < tmp_US_min) tmp_US_min = US_distance_hist[i][j];
      }
      US_distance_avg[i] = (US_distance_hist[i][0] + US_distance_hist[i][1] + US_distance_hist[i][2] + US_distance_hist[i][3]+ US_distance_hist[i][4] - tmp_US_max - tmp_US_min) / 3.0;
    }
        
       
    distance = 75.0;
    
    for(i=0; i<3; i++)
    {
      if( US_distance_avg[i] < distance ) distance = US_distance_avg[i];      
    }
    
    break_value = encoder_value+2400;
    if(break_value > 7999) break_value = 7999;
    
    break_distance = encoder_value; //floating error?
    
    
    break_distance = break_distance/1100 + 10;
    //////////////////////moved target_distance/////////////////////                   
    target_distance = break_distance + 0.5; //error 값이 튈 위험 있음.   
    

    if(fl_run && (distance < break_distance)) //&& (distance >= 8))
    {
      //LEDs_SetBit(2);
      LEDs_ClrBit(0);
      LEDs_ClrBit(1);
      //sum = 10;
      
      // break!!
      DC_Direction_F_ClrVal();
      //DC_Direction_B_ClrVal();
      DC_Direction_B_SetVal();
      DC_F_SetRatio8(0x00U);
      DC_B_SetDutyUS(break_value);
    } 

    if(distance > 74) 
    {
      LEDs_SetBit(1);
      LEDs_ClrBit(0);
      Target_Speed = 6000;
    }
    else
    {
      LEDs_SetBit(0);
      LEDs_ClrBit(1); 
    }

    Target_Speed = (int16_t)( UpdatePID_float(&Distance_pid, (distance - target_distance), (distance - target_distance)) + encoder_value );

    if(Max_Speed < Target_Speed)
    {
      if(tmp < servo_center)
      {
        Target_Speed = Target_Speed - ( ( (int16_t)(Target_Speed - Max_Speed) / 58) * (int16_t)(servo_center-tmp) ) / (int16_t)10;
      }
      else
      {
        Target_Speed = Target_Speed - ( ( (int16_t)(Target_Speed - Max_Speed) / 58) * (int16_t)(tmp - servo_center) ) / (int16_t)10;
      }
    }

      
    if (Target_Speed >5000) Target_Speed = 6000;  
    else if (Target_Speed < -5000) Target_Speed = -4500;       
                  
           
    target_DC = Target_Speed;
      
    tmp2 = UpdatePID(&DC_pid, (target_DC - encoder_value),(target_DC - encoder_value));      
      
      
    if(((Target_Speed - encoder_value) < 100) && ((Target_Speed - encoder_value) > -50))
    {
      LEDs_SetBit(4);
      LEDs_ClrBit(2);
    }
    else if ((encoder_value - Target_Speed) > 100){
        
      LEDs_SetBit(2);
      LEDs_ClrBit(4);
    } 
    else 
    {
      LEDs_ClrBit(4);
      LEDs_ClrBit(2);
    }
     
    if(tmp2 > 7999)               tmp2 = 7999;
    else if(tmp2 < -break_value)  tmp2 = -break_value;
    
    ratio_value = tmp2;
      
     
    // renew all control values
    if(fl_run)
    {
      Servo_SetDutyUS(tmp);      

      if(ratio_value >= 0)
      {
        //LEDs_ClrBit(4);
        DC_Direction_F_SetVal();
        DC_Direction_B_ClrVal();
        DC_F_SetDutyUS(ratio_value);
        DC_B_SetRatio8(0x00U);
      }
      else
      {
        //LEDs_SetBit(4);
        DC_Direction_F_ClrVal();
        DC_Direction_B_SetVal();
        DC_F_SetRatio8(0x00U);
        DC_B_SetDutyUS(ratio_value*(-1));
      }
    }
      
    SevenSEG_Signal_PutVal(0x0FU);
    if(control_cnt%4 == 0)     
    {
      SevenSEG_Data_PutVal(NumToSeg(encoder_F_value%10));         SevenSEG_Signal_PutVal(~0x01);
    }
    else if(control_cnt%4 == 1)
    {
      SevenSEG_Data_PutVal(NumToSeg((encoder_F_value/10)%10));    SevenSEG_Signal_PutVal(~0x02);
    }
    else if(control_cnt%4 == 2) 
    {
      SevenSEG_Data_PutVal(NumToSeg((encoder_F_value/100)%10));   SevenSEG_Signal_PutVal(~0x04);
    }
    else if(control_cnt%4 == 3)
    {
      SevenSEG_Data_PutVal(NumToSeg((encoder_F_value/1000)%10));  SevenSEG_Signal_PutVal(~0x08);   
    }
 
  }
  
  ADConv_EnableEvent();
  ExtInt_Rising_Enable();
  ExtInt_Falling_Enable();
  //LEDs_ClrBit(3);
}

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
void US_echo_timer_OnInterrupt(void)
{
  /* Write your code here ... */

  // one-two
  if(US_cnt)
  {
     
    if((fl_echo_cnt[0]) && (!US0_echo_GetVal()))
    {
      US_distance[0] = ( 0.4705882353 + ((float)echo_cnt*0.01)   )*17; //cm
      fl_echo_cnt[0] = 0U;
    }
    if((fl_echo_cnt[2]) && (!US2_echo_GetVal()))
    {
      US_distance[2] = ( 0.4705882353 + ((float)echo_cnt*0.01)   )*17; //cm
      fl_echo_cnt[2] = 0U;
    }
    if(echo_cnt > 400U)
    {
      US_echo_timer_DisableEvent();
      US_echo_timer_Disable();
      if(fl_echo_cnt[0])  US_distance[0] = 75.0;  // 75cm
      if(fl_echo_cnt[2])  US_distance[2] = 75.0;  // 75cm
      fl_echo_cnt[0] = 0U;
      fl_echo_cnt[2] = 0U;    
    }
    
    echo_cnt++;
  }
  else
  {
    if(echo_cnt > 400U)               // 4ms
    {
      US_echo_timer_DisableEvent();
      US_echo_timer_Disable();
      US_distance[1] = 75.0;    // 75 cm
      echo_cnt = 0U;
    }
    else 
    {
      if(US1_echo_GetVal())
      {
        echo_cnt++;
      }
      else
      {
        US_distance[1] = ( 0.4705882353 + ((float)echo_cnt*0.01)   )*17; //cm
             
        echo_cnt = 0; 
        US_echo_timer_DisableEvent();
        US_echo_timer_Disable();
        //US_distance[1] = ( 0.4705882353 + ((float)echo_cnt*0.01)   )*17; //cm
      }
          
    }
  
  
  }
 
}


/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
