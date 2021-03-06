/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : MICOUT.H
**     Project   : DC17
**     Processor : MC56F8006_32_LQFP
**     Beantype  : ADC
**     Version   : Bean 01.499, Driver 01.00, CPU db: 3.00.169
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 3/28/2009, 9:59 PM
**     Abstract  :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings  :
**         AD control register         : ADC1_ADCSC1A [61568]
**         AD control register         : ADC1_ADCSC2 [61569]
**         AD control register         : ADC1_ADCCFG [61574]
**         AD control register         : ADC1_ADCSC1B [61578]
**         AD control register         : ADC1_ADCRA  [61579]
**         AD control register         : ADC1_ADCRB  [61580]
**         User handling procedure     : not specified
**         Number of conversions       : 1
**         AD resolution               : 12-bit
**
**         Input pins
**
**              Port name              : GPIOC
**              Bit number (in port)   : 4
**              Bit mask of the port   : 16
**              Port data register     : GPIO_C_DR   [61889]
**              Port control register  : GPIO_C_DDR  [61890]
**              Port function register : GPIO_C_PER  [61891]
**
**         Initialization:
**              Conversion             : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-1
**     Contents  :
**         Enable     - byte MICOUT_Enable(void);
**         Disable    - byte MICOUT_Disable(void);
**         Measure    - byte MICOUT_Measure(bool WaitForResult);
**         GetValue16 - byte MICOUT_GetValue16(word *Values);
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __MICOUT
#define __MICOUT

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE MICOUT. */

#include "Cpu.h"




void MICOUT_HWEnDi(void);
/*
** ===================================================================
**     Method      :  MICOUT_HWEnDi (bean ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the bean.
**         The method is called automatically as a part of the Enable and 
**         Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


byte MICOUT_Enable(void);
/*
** ===================================================================
**     Method      :  MICOUT_Enable (bean ADC)
**
**     Description :
**         Enables A/D converter bean. <Events> may be generated
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

byte MICOUT_Disable(void);
/*
** ===================================================================
**     Method      :  MICOUT_Disable (bean ADC)
**
**     Description :
**         Disables A/D converter bean. No <events> will be generated.
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

byte MICOUT_Measure(bool WaitForResult);
/*
** ===================================================================
**     Method      :  MICOUT_Measure (bean ADC)
**
**     Description :
**         This method performs one measurement on all channels that
**         are set in the bean inspector. (Note: If the <number of
**         conversions> is more than one the conversion of A/D channels
**         is performed specified number of times.)
**     Parameters  :
**         NAME            - DESCRIPTION
**         WaitForResult   - Wait for a result of a
**                           conversion. If <interrupt service> is
**                           disabled, A/D peripheral doesn't support
**                           measuring all channels at once or Autoscan
**                           mode property isn't enabled and at the same
**                           time the <number of channel> is greater
**                           than 1, then the WaitForResult parameter is
**                           ignored and the method waits for each
**                           result every time. If the <interrupt
**                           service> is disabled and a <number of
**                           conversions> is greater than 1, the
**                           parameter is ignored and the method also
**                           waits for each result every time.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
** ===================================================================
*/

byte MICOUT_GetValue16(word *Values);
/*
** ===================================================================
**     Method      :  MICOUT_GetValue16 (bean ADC)
**
**     Description :
**         This method returns the last measured values of all channels
**         justified to the left. Compared with <GetValue> method this
**         method returns more accurate result if the <number of
**         conversions> is greater than 1 and <AD resolution> is less
**         than 16 bits. In addition, the user code dependency on <AD
**         resolution> is eliminated.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Values          - Pointer to the array that contains
**                           the measured data.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
** ===================================================================
*/

void MICOUT_Init(void);
/*
** ===================================================================
**     Method      :  MICOUT_Init (bean ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/



/* END MICOUT. */

#endif /* ifndef __MICOUT */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.99 [04.17]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
