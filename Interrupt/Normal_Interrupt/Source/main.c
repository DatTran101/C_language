/*
********************************************************************************
* @file     main.c
* @author   DatTK2
* @version  V1
* @date     11, Jan 2023
* @brief    Examine the special registers when a normal function is in progress
* and a low-priority interrupt occurs
*
*******************************************************************************/

/*******************************************************************************
  Includes
*******************************************************************************/

#include <stdio.h>
#include "MKL46Z4_GPIO_DRV.h"
#include "MKL46Z4_SystemTick_DRV.h"

/*******************************************************************************
   Defination, Macro
*******************************************************************************/

extern STACK_type temp_t;

/*******************************************************************************
   Code
 ******************************************************************************/

/**
 * @brief This Function used to show values of registers after enter interrupt mode.
 * @param
 */
void Show_Signal();

int main(void)
{

  /* Initialize software timer 0 and 1. */
  SystemTick_DRV_Enable(SWTIMER_0);

  /* Pass the address of the Toggle green Led function to the corresponding selected software timer 0. */
  SystemTick_DRV_RegisterCallBack(SWTIMER_0, Show_Signal);

  /* Initialize SystemTick. */
  SystemTick_DRV_Init();

  /* Set alarm time with software timer 0 */
  SystemTick_DRV_SetAlarm_ms(SWTIMER_0, 1);

  while (1)
  {
    //__asm("nop");
  }

} /* End main function. */

void Show_Signal()
{

  /* Print values of special registers */
  printf("----------------\n");
  printf("Values of special Registers after enter interrupt mode.\n");
  printf("\tEXC           : 0x%x\n", temp_t.EXC);
  printf("\tR0            : 0x%x\n", temp_t.R0);
  printf("\tR1            : 0x%x\n", temp_t.R1);
  printf("\tR2            : 0x%x\n", temp_t.R2);
  printf("\tR3            : 0x%x\n", temp_t.R3);
  printf("\tR12           : 0x%x\n", temp_t.R12);
  printf("\tLR            : 0x%x\n", temp_t.LR);
  printf("\tReturn_Addr   : 0x%x\n", temp_t.Return_Addr);
  printf("\txPSR          : 0x%x\n", temp_t.xPSR);

  SystemTick_DRV_Disable(SWTIMER_0);

  printf("\nInterrupt mode finish!\n");
}
