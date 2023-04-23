/*
********************************************************************************
* @file     main.c
* @author   DatTK2
* @version  V1
* @date     11, Jan 2023
* @brief    Examine the special registers when a high-priority jam interrupt is in progress
* and a low-priority interrupt occurs
*
*******************************************************************************/

/*******************************************************************************
  Includes
*******************************************************************************/

#include <stdio.h>
#include "MKL46Z4_GPIO_DRV.h"
#include "MKL46Z4_SystemTick_DRV.h"
#include "MKL46Z4_PIT_DRV.h"

/*******************************************************************************
   Defination, Macro
*******************************************************************************/

extern STACK_type temp_SysTick_t;

extern STACK_type temp_PIT_t;
/*******************************************************************************
   Code
 ******************************************************************************/

/**
 * @brief This Function used to toggle green led.
 * @param
 */
static void Show_LowerPriority_Signal();

static void Show_HigherPriority_Signal();

int main(void)
{

  /* Initialize software timer 0 and 1. */
  SystemTick_DRV_Enable(SWTIMER_0);

  /* Pass the address of the Toggle green Led function to the corresponding selected software timer 0. */
  SystemTick_DRV_RegisterCallBack(SWTIMER_0, Show_HigherPriority_Signal);

  /* Initialize SystemTick. */
  SystemTick_DRV_Init();

  /* Set alarm time with software timer 0 */
  SystemTick_DRV_SetAlarm_ms(SWTIMER_0, 1);

  PIT_DRV_RegisterCallback(Show_LowerPriority_Signal);

  PIT_DRV_Init();

  /* Set priority for PIT and System tick.*/
  NVIC_SetPriority(PIT_IRQn, 1);
  NVIC_SetPriority(SysTick_IRQn, 0);

  while (1)
  {
    __asm("nop");
  }

} /* End main function. */

static void Show_HigherPriority_Signal()
{
  /* Print values of special registers*/
  printf("Values of special Registers in higher priority mode.\n");
  printf("\tEXC:          0x%1.x\n", temp_SysTick_t.EXC);
  printf("\tR0:           0x%x\n", temp_SysTick_t.R0);
  printf("\tR1:           0x%x\n", temp_SysTick_t.R1);
  printf("\tR2:           0x%x\n", temp_SysTick_t.R2);
  printf("\tR3:           0x%x\n", temp_SysTick_t.R3);

  printf("\nEnable lower priority interrupt!\n\n");

  /* Enable PIT used to enter PIT interrupt mode. */
  PIT_DRV_Enable();

  printf("\tR12:          0x%x\n", temp_SysTick_t.R12);
  printf("\tLR:           0x%x\n", temp_SysTick_t.LR);
  printf("\tReturn_Addr:  0x%x\n", temp_SysTick_t.Return_Addr);
  printf("\txPSR:         0x%x\n\n", temp_SysTick_t.xPSR);

  SystemTick_DRV_Disable(SWTIMER_0);

  printf("Fish the higher priority mode!\n");
}

static void Show_LowerPriority_Signal()
{
  /* Print values of special registers*/
  printf("\nValues of special Registers in lower priority mode.\n");
  printf("\tEXC:          0x%x\n", temp_PIT_t.EXC);
  printf("\tR0:           0x%x\n", temp_PIT_t.R0);
  printf("\tR1:           0x%x\n", temp_PIT_t.R1);
  printf("\tR2:           0x%x\n", temp_PIT_t.R2);
  printf("\tR3:           0x%x\n", temp_PIT_t.R3);
  printf("\tR12:          0x%x\n", temp_PIT_t.R12);
  printf("\tLR:           0x%x\n", temp_PIT_t.LR);
  printf("\tReturn_Addr:  0x%x\n", temp_PIT_t.Return_Addr);
  printf("\txPSR:         0x%x\n\n", temp_PIT_t.xPSR);

  PIT_DRV_Disable();

  printf("Fish the lower priority mode!\n");
}