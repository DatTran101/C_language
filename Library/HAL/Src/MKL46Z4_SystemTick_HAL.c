/*
********************************************************************************
* @file     MKL46Z4_SIM_HAL.c
* @author   DatTKD
* @version  V1
* @date     9, Jan 2023
*******************************************************************************/


/*******************************************************************************
  Includes
*******************************************************************************/
#include "MKL46Z4_SystemTick_HAL.h"


/*******************************************************************************
   Defination, Macro
*******************************************************************************/

#define FREQUENCY_DIVIDER            16U        /* The division factor of the selected frequency divider */
#define CONVERSION_FACTOR_TO_1MS     1000U      /* Conversion factor from 1 second to 1 microsecond */

static Set_SWTimer_CallBack func_calledBack;    /* The data type is Set_SWTimer_CallBack, used to hold the address of a function */


/*******************************************************************************
  API
*******************************************************************************/

void SystemTick_HAL_Init()
{
    /* Updates the SystemCoreClock variable. */
    SystemCoreClockUpdate();

    /* Clears the pending bit of an external interrupt.  */
    NVIC_ClearPendingIRQ(SysTick_IRQn);

    /* Enables a device-specific interrupt in the NVIC interrupt controller. */
    NVIC_EnableIRQ(SysTick_IRQn);

    /* Initialize system tick. */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    /* Set value for system tick counter. */
    SysTick->LOAD = ((SystemCoreClock/FREQUENCY_DIVIDER) / CONVERSION_FACTOR_TO_1MS - 1);

    /* Set value for systick current value  register. */
    SysTick->VAL = 0;

    /* Enable system tick. */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

}


void SystemTick_HAL_RegisterCallBack(Set_SWTimer_CallBack func_name)
{
  /* Store the address of the function */
  func_calledBack = func_name;
}

void SysTick_Handler()
{
  /* Executing the function held address by func_calledBack. */
  func_calledBack();

  /* Clear COUNTFAG of systick control and status register. */
  SysTick->CTRL;
}