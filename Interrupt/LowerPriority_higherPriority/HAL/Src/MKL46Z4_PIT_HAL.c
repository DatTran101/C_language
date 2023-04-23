/*
********************************************************************************
* @file     MKL46Z4_SIM_HAL.c
* @author   DatTKD
* @version  V1
* @date     9, Jan 2023
*******************************************************************************/

#include <MKL46Z4.h>
#include <stdlib.h>
#include "MKL46Z4_PIT_HAL.h"

STACK_type temp_PIT_t;

static PIT_DRV_CallBack HAL_func_calledBack = NULL;

void PIT_IRQHandler(void)
{

  register uint32_t STACK_BASE = __get_MSP();

  temp_PIT_t.EXC = STACKING->EXC;
  temp_PIT_t.R0 = STACKING->R0;
  temp_PIT_t.R1 = STACKING->R1;
  temp_PIT_t.R2 = STACKING->R2;
  temp_PIT_t.R3 = STACKING->R3;
  temp_PIT_t.R12 = STACKING->R12;
  temp_PIT_t.LR = STACKING->LR;
  temp_PIT_t.Return_Addr = STACKING->Return_Addr;
  temp_PIT_t.xPSR = STACKING->xPSR;

  HAL_func_calledBack();
}
void PIT_HAL_Init(void)
{

  SIM->SCGC6 |= SIM_SCGC6_PIT(1U);
  PIT->MCR &= ~PIT_MCR_FRZ(1U);
  PIT->MCR &= ~PIT_MCR_MDIS(1U);

  PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE(1U);
  PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN(1U);
}

void PIT_HAL_RegisterCallback(PIT_DRV_CallBack func_name)
{

  HAL_func_calledBack = func_name;
}

void PIT_HAL_Disable(void)
{
  PIT->MCR |= PIT_MCR_MDIS(1);
  PIT->MCR |= PIT_MCR_FRZ_MASK;
  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF(1);
  NVIC_ClearPendingIRQ(PIT_IRQn);
  NVIC_DisableIRQ(PIT_IRQn);
}

void PIT_HAL_Deinit(void)
{
  /* Clears the pending PIT TIMER interrupt */
  NVIC_ClearPendingIRQ(PIT_IRQn);

  /* Disable PIT TIMER interrupt in the NVIC interrupt controller */
  NVIC_DisableIRQ(PIT_IRQn);

  /* Function Point point to NULL */
  HAL_func_calledBack = NULL;
}