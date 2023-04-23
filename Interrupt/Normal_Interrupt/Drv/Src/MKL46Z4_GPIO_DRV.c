/*
********************************************************************************
* @file     MKL46Z4_GPIO_DRV.c
* @author   DatTK2
* @version  V1
* @date     31, Dec 2022
*******************************************************************************/

/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4_GPIO_DRV.h"
#include "MKL46Z4_SIM_HAL.h"
#include "MKL46Z4_PORT_HAL.h"
#include <assert.h>

/*******************************************************************************
  API
*******************************************************************************/

void GPIO_DRV_Init(SCGC5_mode_e SCGC5_mode)
{
  /* Check the input condition of SCGC5_mode, if it is entered incorrectly,
   *it will give an error when starting the debug process
   */
  assert((SCGC5_mode >= PORT_A) && (SCGC5_mode <= PORT_E));
  /* Set System Clock Gating Control Register 5 for corresponding mode */
  SIM_HAL_SCGC5_SetClock(SCGC5_mode);
}

void GPIO_DRV_EnableMUX(PORT_Type *PORTx, PINx_e PINx, MUX_Config_e status)
{
  /* Check the input condition of status, if it is entered incorrectly,
   *it will give an error when starting the debug process
   */
  assert((status == 0) || (status == 1U));
  /* Enable MUX field for corresponding pin*/
  PORT_HAL_EnableMUX(PORTx, PINx, status);
}

void GPIO_DRV_DisableMUX(PORT_Type *PORTx, PINx_e PINx)
{
  /* Check the input condition of PINx, if it is entered incorrectly,
   *it will give an error when starting the debug process
   */
  assert(PINx <= 31U);
  /* Disable MUX field for corresponding pin*/
  PORT_HAL_DisableMUX(PORTx, PINx);
}

void GPIO_DRV_EnablePull(PORT_Type *PORTx, PINx_e PINx)
{

  assert(PINx <= 31U);
  /* Enable "pull mode" for corresponding pin. */
  PORT_HAL_EnablePull(PORTx, PINx);
}

void GPIO_DRV_DisablePull(PORT_Type *PORTx, PINx_e PINx)
{

  assert(PINx <= 31U);
  /* Disable "pull mode" for corresponding pin. */
  PORT_HAL_DisablePull(PORTx, PINx);
}

void GPIO_DRV_Pullup(PORT_Type *PORTx, PINx_e PINx)
{

  assert(PINx <= 31U);
  /* Pullup internal resistor for corresponding pin. */
  PORT_HAL_PullUp(PORTx, PINx);
}

void GPIO_DRV_PullDown(PORT_Type *PORTx, PINx_e PINx)
{

  assert(PINx <= 31U);
  /* Pulldown internal resistor for corresponding pin. */
  PORT_HAL_PullDown(PORTx, PINx);
}

void GPIO_DRV_Config_Output(GPIO_Type *GPIOx, PORT_Type *PORTx, PINx_e PINx)
{

  assert(PINx <= 31U);
  /* Config output for 1 pin. */
  PORT_HAL_EnableMUX(PORTx, PINx, GPIO);
  PORT_HAL_DisablePull(PORTx, PINx);
  GPIO_HAL_Config_Output(GPIOx, PINx);
}

void GPIO_DRV_Write1Pin(GPIO_Type *GPIOx, PINx_e PINx, PINx_State_e state)
{

  assert(PINx <= 31U);
  /* Config output high level for 1 pin. */
  GPIO_HAL_Write1Pin(GPIOx, PINx, state);
}


void GPIO_DRV_Write_PINs_HighLevel(GPIO_Type *GPIOx, PORT_Type *PORTx, uint32_t PINs)
{
  /* Pin, what we wants to config output high level. */
  uint8_t PINx = 0U;

  /* Position pin from 1 to 32. */
  for (PINx = 0U; PINx <= 32U; PINx++)
    /* If the value on the input pin is logic 1, configure that pin to output high level */
    if (((1U << PINx) & PINs) != 0U)
    {

      PORT_HAL_DisablePull(PORTx, PINx);
      PORT_HAL_EnableMUX(PORTx, PINx, GPIO);
      GPIO_HAL_Config_Output(GPIOx, PINx);
      GPIO_HAL_Write1Pin(GPIOx, PINx, SET);
    }
}

void GPIO_DRV_Write_PINs_LowLevel(GPIO_Type *GPIOx, PORT_Type *PORTx, uint32_t PINs)
{
  /* Pin, what we wants to config output high low. */
  uint8_t PINx = 0U;
  /* Position pin from 1 to 32. */
  for (PINx = 0U; PINx <= 32U; PINx++)
    /* If the value on the input pin is logic 1, configure that pin to output low level */
    if (((1U << PINx) & PINs) != 0U)
    {

      PORT_HAL_DisablePull(PORTx, PINx);
      PORT_HAL_EnableMUX(PORTx, PINx, GPIO);
      GPIO_HAL_Config_Output(GPIOx, PINx);
      GPIO_HAL_Write1Pin(GPIOx, PINx, RESET);
    }
}

void GPIO_DRV_Toggle(GPIO_Type *GPIOx, PINx_e PINx)
{

  assert(PINx <= 31U);
  /* Tongle corresponding pin. */
  GPIO_HAL_Toggle(GPIOx, PINx);
}

void GPIO_DRV_Config_Input(GPIO_Type *GPIOx, PORT_Type *PORTx, PINx_e PINx)
{

  assert(PINx <= 31U);
  /* configure input mode for corresponding pin. */
  GPIO_DRV_EnableMUX(PORTC, PINx, GPIO);
  GPIO_HAL_Config_Input(GPIOx, PINx);
}

uint8_t GPIO_DRV_Read_PIN(GPIO_Type *GPIOx, PINx_e PINx)
{

  assert(PINx <= 31U);
  /* Read value at corresponding pin. */
  return GPIO_HAL_Read_PIN(GPIOx, PINx);
}

void GPIO_DRV_DeInit(SCGC5_mode_e SCGC5_mode)
{

  assert((SCGC5_mode >= PORT_A) && (SCGC5_mode <= PORT_E));
  /* Reset System Clock Gating Control Register 5 for corresponding mode */
  SIM_HAL_SCGC5_ResetClock(SCGC5_mode);
}
