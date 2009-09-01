/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : TI0.H
**     Project   : DC17
**     Processor : MC56F8006_32_LQFP
**     Beantype  : TimerInt
**     Version   : Bean 02.157, Driver 02.00, CPU db: 3.00.169
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 3/29/2009, 12:03 AM
**     Abstract  :
**         This bean "TimerInt" implements a periodic interrupt.
**         When the bean and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : TMR0 (16-bit)
**         Compare name                : TMR0_Compare
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 4000000 Hz
**           Initial period/frequency
**             Xtal ticks              : 1000
**             microseconds            : 125
**             seconds (real)          : 0.000125
**             Hz                      : 8000
**             kHz                     : 8
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TMR0_CNTR [61445]
**              Mode                   : TMR0_CTRL [61446]
**              Run                    : TMR0_CTRL [61446]
**              Prescaler              : TMR0_CTRL [61446]
**
**         Compare registers
**              Compare                : TMR0_COMP1 [61440]
**
**         Flip-flop registers
**              Mode                   : TMR0_SCTRL [61447]
**     Contents  :
**         Enable  - byte TI0_Enable(void);
**         Disable - byte TI0_Disable(void);
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __TI0
#define __TI0

/* MODULE TI0. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


byte TI0_Enable(void);
/*
** ===================================================================
**     Method      :  TI0_Enable (bean TimerInt)
**
**     Description :
**         This method enables the bean - it starts the timer. Events
**         may be generated (<DisableEvent>/<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte TI0_Disable(void);
/*
** ===================================================================
**     Method      :  TI0_Disable (bean TimerInt)
**
**     Description :
**         This method disables the bean - it stops the timer. No
**         events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

void TI0_Init(void);
/*
** ===================================================================
**     Method      :  TI0_Init (bean TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void TI0_Interrupt(void);
/*
** ===================================================================
**     Method      :  TI0_Interrupt (bean TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END TI0. */

#endif /* ifndef __TI0 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.99 [04.17]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
