/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PORTCIN.C
**     Project   : DC17
**     Processor : MC56F8006_32_LQFP
**     Beantype  : BitIO
**     Version   : Bean 02.072, Driver 01.17, CPU db: 3.00.169
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 3/23/2009, 7:38 PM
**     Abstract  :
**         This bean "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This bean is set to work in Input direction only.
**         Methods of this bean are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       7             |  GPIOC6_ANB4_PWM2_CMP1_P1
**             ----------------------------------------------------
**
**         Port name                   : GPIOC
**
**         Bit number (in port)        : 6
**         Bit mask of the port        : 64
**
**         Initial direction           : Input (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : GPIO_C_DR [61889]
**         Port control register       : GPIO_C_DDR [61890]
**         Port function register      : GPIO_C_PER [61891]
**
**         Optimization for            : code size
**     Contents  :
**         GetVal - bool PORTCIN_GetVal(void);
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE PORTCIN. */

#include "PORTCIN.h"
/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "Cpu.h"


/*
** ===================================================================
**     Method      :  PORTCIN_GetVal (bean BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This bean is set to work in Input direction only.
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
/*
bool PORTCIN_GetVal(void)

**  This method is implemented as a macro. See PORTCIN.h file.  **

*/

/* END PORTCIN. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.99 [04.17]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
