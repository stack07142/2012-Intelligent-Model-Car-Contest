/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Vectors.c
**     Project   : SCC_02
**     Processor : MC9S12XEP100CAL
**     Version   : Component 01.003, Driver 02.06, CPU db: 3.00.033
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2012-07-15, ���� 12:00
**     Abstract  :
**         This component "MC9S12XEP100_112" implements properties, methods,
**         and events of the CPU.
**     Settings  :
**
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
#include "Cpu.h"
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

/* ISR prototype */
typedef void (*near tIsrFunc)(void);
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
static const tIsrFunc _InterruptVectorTable[] @0xFF10U = { /* Interrupt vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
  /* ISR name                               No.  Address Pri XGATE Name            Description */
  &Cpu_Interrupt,                       /* 0x08  0xFF10   -   -    ivVsi           unused by PE */
  &Cpu_Interrupt,                       /* 0x09  0xFF12   -   -    ivVsyscall      unused by PE */
  &Cpu_Interrupt,                       /* 0x0A  0xFF14   -   -    ivVmpuaccesserr unused by PE */
  &Cpu_Interrupt,                       /* 0x0B  0xFF16   -   no   ivVxsei         unused by PE */
  &Cpu_Interrupt,                       /* 0x0C  0xFF18   1   no   ivVReserved115  unused by PE */
  &Cpu_Interrupt,                       /* 0x0D  0xFF1A   1   no   ivVReserved114  unused by PE */
  &Cpu_Interrupt,                       /* 0x0E  0xFF1C   1   no   ivVReserved113  unused by PE */
  &Cpu_Interrupt,                       /* 0x0F  0xFF1E   1   no   ivVReserved112  unused by PE */
  &Cpu_Interrupt,                       /* 0x10  0xFF20   1   no   ivVReserved111  unused by PE */
  &Cpu_Interrupt,                       /* 0x11  0xFF22   1   no   ivVReserved110  unused by PE */
  &Cpu_Interrupt,                       /* 0x12  0xFF24   1   no   ivVReserved109  unused by PE */
  &Cpu_Interrupt,                       /* 0x13  0xFF26   1   no   ivVReserved108  unused by PE */
  &Cpu_Interrupt,                       /* 0x14  0xFF28   1   no   ivVReserved107  unused by PE */
  &Cpu_Interrupt,                       /* 0x15  0xFF2A   1   no   ivVReserved106  unused by PE */
  &Cpu_Interrupt,                       /* 0x16  0xFF2C   1   no   ivVReserved105  unused by PE */
  &Cpu_Interrupt,                       /* 0x17  0xFF2E   1   no   ivVReserved104  unused by PE */
  &Cpu_Interrupt,                       /* 0x18  0xFF30   1   no   ivVReserved103  unused by PE */
  &Cpu_Interrupt,                       /* 0x19  0xFF32   1   no   ivVReserved102  unused by PE */
  &Cpu_Interrupt,                       /* 0x1A  0xFF34   1   no   ivVReserved101  unused by PE */
  &Cpu_Interrupt,                       /* 0x1B  0xFF36   1   no   ivVReserved100  unused by PE */
  &Cpu_Interrupt,                       /* 0x1C  0xFF38   1   no   ivVReserved99   unused by PE */
  &Cpu_Interrupt,                       /* 0x1D  0xFF3A   1   no   ivVReserved98   unused by PE */
  &Cpu_Interrupt,                       /* 0x1E  0xFF3C   1   no   ivVatd1compare  unused by PE */
  &Cpu_Interrupt,                       /* 0x1F  0xFF3E   1   no   ivVatd0compare  unused by PE */
  &Cpu_Interrupt,                       /* 0x20  0xFF40   1   no   ivVtimpaie      unused by PE */
  &Cpu_Interrupt,                       /* 0x21  0xFF42   1   no   ivVtimpaaovf    unused by PE */
  &Cpu_Interrupt,                       /* 0x22  0xFF44   1   no   ivVtimovf       unused by PE */
  &Cpu_Interrupt,                       /* 0x23  0xFF46   1   no   ivVtimch7       unused by PE */
  &Cpu_Interrupt,                       /* 0x24  0xFF48   1   no   ivVtimch6       unused by PE */
  &Cpu_Interrupt,                       /* 0x25  0xFF4A   1   no   ivVtimch5       unused by PE */
  &Cpu_Interrupt,                       /* 0x26  0xFF4C   1   no   ivVtimch4       unused by PE */
  &Cpu_Interrupt,                       /* 0x27  0xFF4E   1   no   ivVtimch3       unused by PE */
  &Cpu_Interrupt,                       /* 0x28  0xFF50   1   no   ivVtimch2       unused by PE */
  &Cpu_Interrupt,                       /* 0x29  0xFF52   1   no   ivVtimch1       unused by PE */
  &Control_Timer_Interrupt,             /* 0x2A  0xFF54   4   no   ivVtimch0       used by PE */
  &Cpu_Interrupt,                       /* 0x2B  0xFF56   1   no   ivVsci7         unused by PE */
  &Cpu_Interrupt,                       /* 0x2C  0xFF58   1   no   ivVpit7         unused by PE */
  &Cpu_Interrupt,                       /* 0x2D  0xFF5A   1   no   ivVpit6         unused by PE */
  &Cpu_Interrupt,                       /* 0x2E  0xFF5C   1   no   ivVpit5         unused by PE */
  &Cpu_Interrupt,                       /* 0x2F  0xFF5E   1   no   ivVpit4         unused by PE */
  &Cpu_Interrupt,                       /* 0x30  0xFF60   1   no   ivVReserved79   unused by PE */
  &Cpu_Interrupt,                       /* 0x31  0xFF62   1   no   ivVReserved78   unused by PE */
  &Cpu_Interrupt,                       /* 0x32  0xFF64   1   no   ivVxst7         unused by PE */
  &Cpu_Interrupt,                       /* 0x33  0xFF66   1   no   ivVxst6         unused by PE */
  &Cpu_Interrupt,                       /* 0x34  0xFF68   1   no   ivVxst5         unused by PE */
  &Cpu_Interrupt,                       /* 0x35  0xFF6A   1   no   ivVxst4         unused by PE */
  &Cpu_Interrupt,                       /* 0x36  0xFF6C   1   no   ivVxst3         unused by PE */
  &Cpu_Interrupt,                       /* 0x37  0xFF6E   1   no   ivVxst2         unused by PE */
  &Cpu_Interrupt,                       /* 0x38  0xFF70   1   no   ivVxst1         unused by PE */
  &Cpu_Interrupt,                       /* 0x39  0xFF72   1   no   ivVxst0         unused by PE */
  &Cpu_Interrupt,                       /* 0x3A  0xFF74   1   no   ivVpit3         unused by PE */
  &Cpu_Interrupt,                       /* 0x3B  0xFF76   1   no   ivVpit2         unused by PE */
  &US_echo_timer_Interrupt,             /* 0x3C  0xFF78   4   no   ivVpit1         used by PE */
  &Cpu_Interrupt,                       /* 0x3D  0xFF7A   1   no   ivVpit0         unused by PE */
  &Cpu_Interrupt,                       /* 0x3E  0xFF7C   1   -    ivVhti          unused by PE */
  &Cpu_Interrupt,                       /* 0x3F  0xFF7E   1   no   ivVapi          unused by PE */
  &Cpu_Interrupt,                       /* 0x40  0xFF80   1   no   ivVlvi          unused by PE */
  &Cpu_Interrupt,                       /* 0x41  0xFF82   1   no   ivVReserved62   unused by PE */
  &Cpu_Interrupt,                       /* 0x42  0xFF84   1   no   ivVsci5         unused by PE */
  &Cpu_Interrupt,                       /* 0x43  0xFF86   1   no   ivVsci4         unused by PE */
  &Cpu_Interrupt,                       /* 0x44  0xFF88   1   no   ivVsci3         unused by PE */
  &Cpu_Interrupt,                       /* 0x45  0xFF8A   1   no   ivVsci2         unused by PE */
  &Cpu_Interrupt,                       /* 0x46  0xFF8C   1   no   ivVpwmesdn      unused by PE */
  &Cpu_Interrupt,                       /* 0x47  0xFF8E   1   no   ivVportp        unused by PE */
  &Cpu_Interrupt,                       /* 0x48  0xFF90   1   no   ivVcan4tx       unused by PE */
  &Cpu_Interrupt,                       /* 0x49  0xFF92   1   no   ivVcan4rx       unused by PE */
  &Cpu_Interrupt,                       /* 0x4A  0xFF94   1   no   ivVcan4err      unused by PE */
  &Cpu_Interrupt,                       /* 0x4B  0xFF96   1   no   ivVcan4wkup     unused by PE */
  &Cpu_Interrupt,                       /* 0x4C  0xFF98   1   no   ivVcan3tx       unused by PE */
  &Cpu_Interrupt,                       /* 0x4D  0xFF9A   1   no   ivVcan3rx       unused by PE */
  &Cpu_Interrupt,                       /* 0x4E  0xFF9C   1   no   ivVcan3err      unused by PE */
  &Cpu_Interrupt,                       /* 0x4F  0xFF9E   1   no   ivVcan3wkup     unused by PE */
  &Cpu_Interrupt,                       /* 0x50  0xFFA0   1   no   ivVcan2tx       unused by PE */
  &Cpu_Interrupt,                       /* 0x51  0xFFA2   1   no   ivVcan2rx       unused by PE */
  &Cpu_Interrupt,                       /* 0x52  0xFFA4   1   no   ivVcan2err      unused by PE */
  &Cpu_Interrupt,                       /* 0x53  0xFFA6   1   no   ivVcan2wkup     unused by PE */
  &Cpu_Interrupt,                       /* 0x54  0xFFA8   1   no   ivVcan1tx       unused by PE */
  &Cpu_Interrupt,                       /* 0x55  0xFFAA   1   no   ivVcan1rx       unused by PE */
  &Cpu_Interrupt,                       /* 0x56  0xFFAC   1   no   ivVcan1err      unused by PE */
  &Cpu_Interrupt,                       /* 0x57  0xFFAE   1   no   ivVcan1wkup     unused by PE */
  &Cpu_Interrupt,                       /* 0x58  0xFFB0   1   no   ivVcan0tx       unused by PE */
  &Cpu_Interrupt,                       /* 0x59  0xFFB2   1   no   ivVcan0rx       unused by PE */
  &Cpu_Interrupt,                       /* 0x5A  0xFFB4   1   no   ivVcan0err      unused by PE */
  &Cpu_Interrupt,                       /* 0x5B  0xFFB6   1   no   ivVcan0wkup     unused by PE */
  &Cpu_Interrupt,                       /* 0x5C  0xFFB8   1   no   ivVflash        unused by PE */
  &Cpu_Interrupt,                       /* 0x5D  0xFFBA   1   no   ivVflashfd      unused by PE */
  &Cpu_Interrupt,                       /* 0x5E  0xFFBC   1   no   ivVspi2         unused by PE */
  &Cpu_Interrupt,                       /* 0x5F  0xFFBE   1   no   ivVspi1         unused by PE */
  &Cpu_Interrupt,                       /* 0x60  0xFFC0   1   no   ivViic0         unused by PE */
  &Cpu_Interrupt,                       /* 0x61  0xFFC2   1   no   ivVsci6         unused by PE */
  &Cpu_Interrupt,                       /* 0x62  0xFFC4   1   no   ivVcrgscm       unused by PE */
  &Cpu_Interrupt,                       /* 0x63  0xFFC6   1   no   ivVcrgplllck    unused by PE */
  &Cpu_Interrupt,                       /* 0x64  0xFFC8   1   no   ivVectpabovf    unused by PE */
  &Cpu_Interrupt,                       /* 0x65  0xFFCA   1   no   ivVectmdcu      unused by PE */
  &Cpu__ivVporth,                       /* 0x66  0xFFCC   4   no   ivVporth        used by PE */
  &Cpu_Interrupt,                       /* 0x67  0xFFCE   1   no   ivVportj        unused by PE */
  &Cpu_Interrupt,                       /* 0x68  0xFFD0   1   no   ivVatd1         unused by PE */
  &ADConv_Interrupt,                    /* 0x69  0xFFD2   4   no   ivVatd0         used by PE */
  &Cpu_Interrupt,                       /* 0x6A  0xFFD4   1   no   ivVsci1         unused by PE */
  &Cpu_Interrupt,                       /* 0x6B  0xFFD6   1   no   ivVsci0         unused by PE */
  &Cpu_Interrupt,                       /* 0x6C  0xFFD8   1   no   ivVspi0         unused by PE */
  &Cpu_Interrupt,                       /* 0x6D  0xFFDA   1   no   ivVectpaie      unused by PE */
  &Cpu_Interrupt,                       /* 0x6E  0xFFDC   1   no   ivVectpaaovf    unused by PE */
  &Cpu_Interrupt,                       /* 0x6F  0xFFDE   1   no   ivVectovf       unused by PE */
  &Cpu_Interrupt,                       /* 0x70  0xFFE0   1   no   ivVectch7       unused by PE */
  &Cpu_Interrupt,                       /* 0x71  0xFFE2   1   no   ivVectch6       unused by PE */
  &Cpu_Interrupt,                       /* 0x72  0xFFE4   1   no   ivVectch5       unused by PE */
  &Cpu_Interrupt,                       /* 0x73  0xFFE6   1   no   ivVectch4       unused by PE */
  &Cpu_Interrupt,                       /* 0x74  0xFFE8   1   no   ivVectch3       unused by PE */
  &Cpu_Interrupt,                       /* 0x75  0xFFEA   1   no   ivVectch2       unused by PE */
  &Cpu_Interrupt,                       /* 0x76  0xFFEC   1   no   ivVectch1       unused by PE */
  &Cpu_Interrupt,                       /* 0x77  0xFFEE   1   no   ivVectch0       unused by PE */
  &Cpu_Interrupt,                       /* 0x78  0xFFF0   1   no   ivVrti          unused by PE */
  &Cpu_Interrupt,                       /* 0x79  0xFFF2   1   no   ivVirq          unused by PE */
  &Cpu_Interrupt,                       /* 0x7A  0xFFF4   -   -    ivVxirq         unused by PE */
  &Cpu_Interrupt,                       /* 0x7B  0xFFF6   -   -    ivVswi          unused by PE */
  &Cpu_Interrupt                        /* 0x7C  0xFFF8   -   -    ivVtrap         unused by PE */
};

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
static const tIsrFunc _ResetVectorTable[] @0xFFFAU = { /* Reset vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
  /* Reset handler name                    Address Name             Description */
  &_EntryPoint,                         /* 0xFFFA  ivVcop           unused by PE */
  &_EntryPoint,                         /* 0xFFFC  ivVclkmon        unused by PE */
  &_EntryPoint                          /* 0xFFFE  ivVreset         used by PE */
};
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
