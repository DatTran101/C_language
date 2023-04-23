/*
********************************************************************************
* @file     MKL46Z4_SIM_HAL.c
* @author   DatTKD
* @version  V1
* @date     30, Dec 2022
******************************************************************************/

/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4_PORT_HAL.h"

/*******************************************************************************
  API
*******************************************************************************/

void PORT_HAL_EnableMUX(PORT_Type *PORTx, uint8_t PINx, uint8_t status)
{
  /* Set MUX field is equal to "status value"  */
  PORTx->PCR[PINx] |= PORT_PCR_MUX(status);
}

void PORT_HAL_DisableMUX(PORT_Type *PORTx, uint8_t PINx)
{
  /* Clear bits of MUX field to disable MUX field (or config ananlog mode) */
  PORTx->PCR[PINx] &= ~PORT_PCR_MUX(PORT_PCR_MUX_MASK);
}

void PORT_HAL_EnablePull(PORT_Type *PORTx, uint8_t PINx)
{
  /* Set bit of pull enable field to enable "pull enable field" */
  PORTx->PCR[PINx] |= PORT_PCR_PE(1U);
}

void PORT_HAL_DisablePull(PORT_Type *PORTx, uint8_t PINx)
{
  /* Clear bit of pull enable field to disable "pull enable field" */
  PORTx->PCR[PINx] &= ~PORT_PCR_PE(1U);
}

void PORT_HAL_PullUp(PORT_Type *PORTx, uint8_t PINx)
{
  /* Set bit of pull section field to pullup internal resistor*/
  PORTx->PCR[PINx] |= PORT_PCR_PS(1U);
}

void PORT_HAL_PullDown(PORT_Type *PORTx, uint8_t PINx)
{
  /* Clear bit of pull section field to pulldown internal resistor */
  PORTx->PCR[PINx] &= ~PORT_PCR_PS(1U);
}
