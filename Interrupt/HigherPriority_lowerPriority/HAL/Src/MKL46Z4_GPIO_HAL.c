/*
********************************************************************************
* @file     MKL46Z4_GPIO_HAL.c
* @author   DatTK2
* @version  V1
* @date     31, Dec 2022
******************************************************************************/

/*******************************************************************************
  Includes
*******************************************************************************/
#include "MKL46Z4_GPIO_HAL.h"

/*******************************************************************************
  API
*******************************************************************************/

void GPIO_HAL_Config_Output(GPIO_Type *GPIOx, uint8_t PINx)
{
  /* Set pin to config output */
  GPIOx->PDDR |= (1U << PINx);
}

void GPIO_HAL_Write1Pin(GPIO_Type *GPIOx, uint8_t PINx, PINx_State_e state)
{
  if (0 == state)
    /* Set pin to config output low level*/
    GPIOx->PCOR |= (1U << PINx);
  else
  {
    /* Set pin to config output high level*/
    GPIOx->PSOR |= (1U << PINx);
  }
}

void GPIO_HAL_Toggle(GPIO_Type *GPIOx, uint8_t PINx)
{
  /* Set pin to config toggle corresponding pin*/
  GPIOx->PTOR |= (1U << PINx);
}

void GPIO_HAL_Config_Input(GPIO_Type *GPIOx, uint8_t PINx)
{
  /* Clear pin to config input */
  GPIOx->PDDR &= ~((uint32_t)1U << PINx);
}

uint8_t GPIO_HAL_Read_PIN(GPIO_Type *GPIOx, uint8_t PINx)
{
  /* Read  value of corresponding pin*/
  return (uint8_t)((GPIOx->PDIR >> PINx) & 1U);
}
