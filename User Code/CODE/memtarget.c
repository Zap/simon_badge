/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* File: memTarget.c */

#include "port.h"
#include "mem.h"
#include "arch.h"
#include "assert.h"
#include <string.h>
#include <stdio.h>


/*******************************************************
* specific memory Package for 56F8006_32_LQFP
*******************************************************/

/*****************************************************************************
*
* Module:
*    memIsIM()
*
* Description:
*    This function determines if the pointer to memory passed in is
*    in internal memory of the 56F8006_32_LQFP.
*
* Returns:
*    true  - if memory is in internal memory
*    false - if memory is not in internal memory
*
* Global Data:
*    None
*
* Arguments:
*    memblock - void * pointer to a memory location
*
* Range Issues:
*
* Special Issues:
*
*******************************************************************************/
#pragma warn_unusedarg off
bool    memIsIM     (void * memblock)
{
  return true;  /* ALL memory in 56F8006_32_LQFP is internal */
}
#pragma warn_unusedarg reset

/*****************************************************************************
*
* Module:
*    memIsEM()
*
* Description:
*    This function determines if the pointer to memory passed in is
*    in external memory of the 56F8006_32_LQFP.
*
* Returns:
*    true  - if memory is in external memory
*    false - if memory is not in external memory
*
* Global Data:
*    None
*
* Arguments:
*    memblock - void * pointer to a memory location
*
* Range Issues:
*
* Special Issues:
*
*******************************************************************************/
#pragma warn_unusedarg off
bool    memIsEM     (void * memblock)
{
  return false; /* NO memory in 56F8006_32_LQFP is external */
}
#pragma warn_unusedarg reset
