/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Term1.H
**     Project   : DC17
**     Processor : MC56F8006_32_LQFP
**     Beantype  : Term
**     Version   : Bean 02.028, Driver 03.18, CPU db: 3.00.169
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 3/21/2009, 1:50 PM
**     Abstract  :
**
**     Settings  :
**
**     Contents  :
**         SendStr  - void Term1_SendStr(uint8_t *str);
**         SendNum  - void Term1_SendNum(int32_t number);
**         SendChar - void Term1_SendChar(uint8_t Val);
**         MoveTo   - void Term1_MoveTo(uint8_t x, uint8_t y);
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __Term1
#define __Term1

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE Term1. */

#include "Cpu.h"


void Term1_SendChar(uint8_t Val);
/*
** ===================================================================
**     Method      :  Term1_SendChar (bean Term)
**
**     Description :
**         Send char to terminal.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Val             - Char to send
**     Returns     : Nothing
** ===================================================================
*/

void Term1_SendStr(void *str);
/*
** ===================================================================
**     Method      :  Term1_SendStr (bean Term)
**
**     Description :
**         Send string to terminal.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * str             - Pointer to a string variable
**     Returns     : Nothing
** ===================================================================
*/

void Term1_SendNum(int32_t number);
/*
** ===================================================================
**     Method      :  Term1_SendNum (bean Term)
**
**     Description :
**         Send number to terminal.
**     Parameters  :
**         NAME            - DESCRIPTION
**         number          - Long number
**     Returns     : Nothing
** ===================================================================
*/

void Term1_MoveTo(uint8_t x,uint8_t y);
/*
** ===================================================================
**     Method      :  Term1_MoveTo (bean Term)
**
**     Description :
**         Move cursor to position x, y. Range of coordinates can be
**         from 1 to the size, which depends on the used terminal.
**         Position [1,1] represents the upper left corner.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - Column number
**         y               - Row number
**     Returns     : Nothing
** ===================================================================
*/


/* END Term1. */

#endif /* ifndef __Term1 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.99 [04.17]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
