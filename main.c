/**************************************************************************//**
 * @file     main.c
 * @version  V2.00
 * @brief    NUC029xEE Series GPIO Driver Sample Code
 *
 * @note
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


#define PLL_CLOCK           72000000

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);

    /* Waiting for external XTAL clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);



}


volatile uint32_t TimeTick = 0;
void SysTick_Handler(void)             
{
    TimeTick++;
	PB2=~PB2;
}

void config_systick(uint32_t us)  
{
    SysTick->LOAD =  (36*us)-1;      //systick clock=hclk/2=72000000/2=36000000;        
    SysTick->VAL   =     0;                  
    SysTick->CTRL  |=  SysTick_CTRL_TICKINT_Msk   | SysTick_CTRL_ENABLE_Msk; 
}
/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();
    GPIO_SetMode(PB, BIT2, GPIO_PMD_OUTPUT);
    /* Lock protected registers */
    SYS_LockReg();
    config_systick(100);
	  while(1)
	  {
	  }
	
  
}

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
