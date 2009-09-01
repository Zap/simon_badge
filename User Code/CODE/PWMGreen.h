/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PWMGreen.H
**     Project   : DC17
**     Processor : MC56F8006_32_LQFP
**     Beantype  : PWM
**     Version   : Bean 02.207, Driver 02.00, CPU db: 3.00.169
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 3/28/2009, 9:59 PM
**     Abstract  :
**         This bean implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
**     Settings  :
**         Used output pin             : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       28            |  GPIOA1_PWM1
**             ----------------------------------------------------
**
**         Timer name                  : PWM_Timer [1-bit]
**         Counter                     : PWM_CNTR  [61476]
**         Mode register               : PWM_CTRL  [61472]
**         Run register                : PWM_CTRL  [61472]
**         Prescaler                   : PWM_CTRL  [61472]
**         Compare register            : PWM_VAL1  [61479]
**         Flip-flop register          : PWM_CNFG  [61488]
**
**         User handling procedure     : not specified
**
**         Port name                   : GPIOA
**         Bit number (in port)        : 1
**         Bit mask of the port        : 2
**         Port data register          : GPIO_A_DR [61825]
**         Port control register       : GPIO_A_DDR [61826]
**         Port function register      : GPIO_A_PER [61827]
**
**         Initialization:
**              Output level           : high
**              Timer                  : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 4000000 Hz
**           Initial value of            period     pulse width
**             Xtal ticks              : 8000       8
**             microseconds            : 1000       1
**             milliseconds            : 1          0
**             seconds (real)          : 0.001      0.000001
**
**     Contents  :
**         Enable     - byte PWMGreen_Enable(void);
**         Disable    - byte PWMGreen_Disable(void);
**         SetRatio16 - byte PWMGreen_SetRatio16(word Ratio);
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __PWMGreen
#define __PWMGreen

/* MODULE PWMGreen. */

#include "Cpu.h"

#define PWMGreen_PERIOD_VALUE 4000UL   /* Initial period value in ticks of the timer. It is available only if the bean is enabled in high speed mode. */
#define PWMGreen_PERIOD_VALUE_HIGH 4000UL /* Period value in ticks of the timer in high speed mode. It is available only if the bean is enabled in high speed mode. */

byte PWMGreen_Enable(void);
/*
** ===================================================================
**     Method      :  PWMGreen_Enable (bean PWM)
**
**     Description :
**         This method enables the bean - it starts the signal
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

byte PWMGreen_Disable(void);
/*
** ===================================================================
**     Method      :  PWMGreen_Disable (bean PWM)
**
**     Description :
**         This method disables the bean - it stops the signal
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

byte PWMGreen_SetRatio16(word Ratio);
/*
** ===================================================================
**     Method      :  PWMGreen_SetRatio16 (bean PWM)
**
**     Description :
**         This method sets a new duty-cycle ratio.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Ratio      - Ratio is expressed as an 16-bit unsigned integer
**                      number. 0 - 65535 value is proportional
**                      to ratio 0 - 100%
**         Note: Calculated duty depends on the timer possibilities
**               and on the selected period.
**     Returns     :
**         ---        - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

void PWMGreen_Init(void);
/*
** ===================================================================
**     Method      :  PWMGreen_Init (bean PWM)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


/* END PWMGreen. */

#endif /* ifndef __PWMGreen */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.99 [04.17]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/