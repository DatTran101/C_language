/*
********************************************************************************
* @file     MKL46Z4_PIT_DRV.c
* @author   DatTK2
* @version  V1
* @date     16, Jan 2023
*******************************************************************************/


/*******************************************************************************
  Includes
*******************************************************************************/

#include <stdlib.h>
#include "MKL46Z4.h"
#include "MKL46Z4_PIT_HAL.h"
#include "MKL46Z4_PIT_DRV.h"


static PIT_UserFunc_CallBack DRV_func_calledBack = NULL;

static void PIT_DRV_Handler(void);

void PIT_DRV_Init(void)
{
    /* Initilize PIT*/
    PIT_HAL_Init();
    /* Called by function pointer at the hal layer */
    PIT_HAL_RegisterCallback(PIT_DRV_Handler);
}

void PIT_DRV_Enable(void)
{
    NVIC_ClearPendingIRQ(PIT_IRQn);
    NVIC_EnableIRQ(PIT_IRQn);
    NVIC_SetPendingIRQ(PIT_IRQn);
}

void PIT_DRV_Disable(void)
{
    PIT_HAL_Disable();
}

void PIT_DRV_RegisterCallback(PIT_UserFunc_CallBack func_name)
{

    DRV_func_calledBack = func_name;
}

static void PIT_DRV_Handler(void)
{
    if (NULL != DRV_func_calledBack)
    {
        DRV_func_calledBack();
    }
}

void PIT_DRV_Deinit(void)
{
    PIT_HAL_Deinit();
}