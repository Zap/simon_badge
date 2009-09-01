/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PWMRed.C
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
**                       29            |  GPIOA0_PWM0
**             ----------------------------------------------------
**
**         Timer name                  : PWM_Timer [1-bit]
**         Counter                     : PWM_CNTR  [61476]
**         Mode register               : PWM_CTRL  [61472]
**         Run register                : PWM_CTRL  [61472]
**         Prescaler                   : PWM_CTRL  [61472]
**         Compare register            : PWM_VAL0  [61478]
**         Flip-flop register          : PWM_CNFG  [61488]
**
**         User handling procedure     : not specified
**
**         Port name                   : GPIOA
**         Bit number (in port)        : 0
**         Bit mask of the port        : 1
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
**         Enable     - byte PWMRed_Enable(void);
**         Disable    - byte PWMRed_Disable(void);
**         SetRatio16 - byte PWMRed_SetRatio16(word Ratio);
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


/* MODULE PWMRed. */

#include "PWMRed.h"

static bool EnUser;                    /* Enable/Disable device by user */
static word RatioStore;                /* Ratio of L-level to H-level */

/* Internal method prototypes */
static void HWEnDi(void);
static void SetRatio(void);

#define SetPV(Val) setRegBitGroup(PWM_CTRL,PRSC,(Val))

/*
** ===================================================================
**     Method      :  SetRatio (bean PWM)
**
**     Description :
**         Calculates and sets new duty ratio. The method is called 
**         automatically as a part of several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetRatio(void)
{
  setReg(PWM_VAL0,((getReg(PWM_CMOD)+1) * (dword)RatioStore) >> 16); /* Calculate new value according to the given ratio */
  setRegBit(PWM_CTRL,LDOK);            /* Load counter and modulo registers into buffers */
}
/*
** ===================================================================
**     Method      :  HWEnDi (bean PWM)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the bean.
**         The method is called automatically as a part of the Enable and 
**         Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (EnUser) {                        /* Enable device? */
    setRegBit(PWM_CTRL,LDOK);          /* Load counter and modulo registers into buffers */
    clrRegBits(PWM_OUT,256);           /* Enable channel output */
  }
  else {                               /* Disable device? */
    setRegBits(PWM_OUT,256);           /* Disable channel output */
  }
}

/*
** ===================================================================
**     Method      :  PWMRed_Enable (bean PWM)
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
byte PWMRed_Enable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    HWEnDi();                          /* Enable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  PWMRed_Disable (bean PWM)
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
byte PWMRed_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    HWEnDi();                          /* Disable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  PWMRed_SetRatio16 (bean PWM)
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
byte PWMRed_SetRatio16(word Ratio)
{
  RatioStore = Ratio;                  /* Store new value of the ratio */
  SetRatio();                          /* Calculate and set up new appropriate duty value */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  PWMRed_Init (bean PWM)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PWMRed_Init(void)
{
  RatioStore = (word)65U;              /* Store initial value of the ratio */
  /* PWM_ICCTRL: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,PEC2=0,PEC1=0,PEC0=0,ICC2=0,ICC1=0,ICC0=0 */
  setReg(PWM_ICCTRL,0);                /* Set up Internal Correction Control Register */
  /* PWM_DMAP1: DISMAP_15_0=0 */
  setReg(PWM_DMAP1,0);                 /* Set up PWM Disable Mapping Register 1 */
  /* PWM_DMAP2: DISMAP_23_16=0 */
  setReg(PWM_DMAP2,0);                 /* Set up PWM Disable Mapping Register 2 */
  /* PWM_OUT: PAD_EN=0,??=0,OUTCTL5=1,OUTCTL4=1,OUTCTL3=1,OUTCTL2=1,OUTCTL1=1,OUTCTL0=1,??=0,??=0,OUT5=1,OUT4=1,OUT3=1,OUT2=1,OUT1=1,OUT0=1 */
  setReg(PWM_OUT,16191);               /* Set up Output Control Register */
  setReg(PWM_DTIM0,0);                 /* Set up Dead-Time Register */
  setReg(PWM_DTIM1,0);                 /* Set up Dead-Time 1 Register */
  setReg(PWM_SCTRL,0);                 /* Set up PWM Source Control Register */
  /* PWM_CCTRL: ENHA=0,nBX=0,MSK5=1,MSK4=1,MSK3=1,MSK2=1,MSK1=1,MSK0=1,??=0,??=0,VLMODE=0,??=0,SWP45=0,SWP23=0,SWP01=0 */
  setReg(PWM_CCTRL,16128);             /* Set up PWM Chanel Control Register */
  /* PWM_CNFG: ??=0,DBG_EN=0,WAIT_EN=0,EDG=1,??=0,TOPNEG45=0,TOPNEG23=0,TOPNEG01=0,??=0,BOTNEG45=0,BOTNEG23=0,BOTNEG01=0,INDEP45=1,INDEP23=1,INDEP01=1,WP=0 */
  setReg(PWM_CNFG,4110);               /* Set up PWM configure register */
  setReg(PWM_CNTR,0);                  /* Reset counter */
  EnUser = TRUE;                       /* Enable device */
  setReg(PWM_VAL0,4);                  /* Store initial value to the duty-compare register */
  setReg(PWM_CMOD,4000);               /* and to the period register */
  SetPV((byte)0);                      /* Set prescaler register according to the selected high speed CPU mode */
}

/* END PWMRed. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.99 [04.17]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/