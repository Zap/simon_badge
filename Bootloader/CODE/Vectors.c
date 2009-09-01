/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Vectors.C
**     Project   : static_bootloader
**     Processor : MC56F8006_32_LQFP
**     Version   : Bean 01.013, Driver 02.01, CPU db: 3.00.169
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 4/6/2009, 11:56 AM
**     Abstract  :
**
**     Comment   :
**         In Vectors.c, change: 
**           JSR fisr_sci_rx_full 
**         to
**           JMP  fisr_sci_rx_full 
**     Settings  :
**
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#include "Cpu.h"
#include "SCI1.h"
#include "Bits1.h"
#include "Events.h"

/*lint -save -e40 -e718 -e746 -e745 -e939 -e937 -e957 -e505 -e522 -e533 Disable MISRA rule (20,75,71,53,83) checking. */

extern void _EntryPoint(void);         /* Startup routine */

volatile asm void _vectboot(void);
#pragma define_section interrupt_vectorsboot "interrupt_vectorsboot.text"  RX
#pragma section interrupt_vectorsboot begin
volatile asm void _vectboot(void) {
  JMP  _EntryPoint                     /* Reset vector (Used) */
  JMP  _EntryPoint                     /* COP reset vector (Used) */
}
#pragma section interrupt_vectorsboot end

volatile asm void _vect(void);
#pragma define_section interrupt_vectors "interrupt_vectors.text"  RX
#pragma section interrupt_vectors begin
volatile asm void _vect(void) {
  JMP  _EntryPoint                     /* Interrupt no. 0 (Used)   - ivINT_Reset */
  JMP  _EntryPoint                     /* Interrupt no. 1 (Used)   - ivINT_COPReset  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 2 (Unused) - ivINT_Illegal_Instruction  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 3 (Unused) - ivINT_HWStackOverflow  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 4 (Unused) - ivINT_MisalignedLongWordAccess  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 5 (Unused) - ivINT_OnCE_StepCounter  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 6 (Unused) - ivINT_OnCE_BreakpointUnit  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 7 (Unused) - ivINT_OnCE_TraceBuffer  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 8 (Unused) - ivINT_OnCE_TxREmpty  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 9 (Unused) - ivINT_OnCE_RxRFull  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 10 (Unused) - ivINT_PMC_OutOfReg_LVI  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 11 (Unused) - ivINT_PLL_LossOfLock_LossOfRefClk  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 12 (Unused) - ivINT_ADC0_Complete  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 13 (Unused) - ivINT_ADC1_Complete  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 14 (Unused) - ivINT_PWM_Reload_Fault  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 15 (Unused) - ivINT_CMP0_FlagRisingFalling  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 16 (Unused) - ivINT_CMP1_FlagRisingFalling  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 17 (Unused) - ivINT_CMP2_FlagRisingFalling  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 18 (Unused) - ivINT_HFM_ERR_CC_CBE  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 19 (Unused) - ivINT_SPI_Rx_Full_Over_ModeFault  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 20 (Unused) - ivINT_SPI_Tx_Empty  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 21 (Unused) - ivINT_SCI_Tx_Empty_Idle  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 22 (Unused) - ivINT_SCI_Rx_Full_Over_Error  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 23 (Unused) - ivINT_I2C  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 24 (Unused) - ivINT_PIT  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 25 (Unused) - ivINT_TMR0  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 26 (Unused) - ivINT_TMR1  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 27 (Unused) - ivINT_GPIO_A  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 28 (Unused) - ivINT_GPIO_B  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 29 (Unused) - ivINT_GPIO_C  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 30 (Unused) - ivINT_GPIO_D  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 31 (Unused) - ivINT_GPIO_E  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 32 (Unused) - ivINT_GPIO_F  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 33 (Unused) - ivINT_RTC  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 34 (Unused) - ivReserved0  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 35 (Unused) - ivReserved1  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 36 (Unused) - ivReserved2  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 37 (Unused) - ivReserved3  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 38 (Unused) - ivReserved4  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 39 (Unused) - ivReserved5  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 40 (Unused) - ivINT_SW0  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 41 (Unused) - ivINT_SW1  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 42 (Unused) - ivINT_SW2  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 43 (Unused) - ivINT_SW3  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 44 (Unused) - ivINT_LP  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 45 (Unused) - ivINT_USER1  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 46 (Unused) - ivINT_USER2  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 47 (Unused) - ivINT_USER3  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 48 (Unused) - ivINT_USER4  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 49 (Unused) - ivINT_USER5  */
  JMP  fisr_sci_rx_full                /* Interrupt no. 50 (Used)   - ivINT_USER6  */
}
#pragma section interrupt_vectors end

/*lint -restore */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.99 [04.17]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/