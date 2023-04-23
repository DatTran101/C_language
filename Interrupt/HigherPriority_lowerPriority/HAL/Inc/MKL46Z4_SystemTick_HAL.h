/*
********************************************************************************
* @file     MKL46Z4_SYSTEMTICK_HAL.h
* @author   DatTK2
* @version  V1
* @date     9, Jan 2023
*******************************************************************************/

#ifndef _MKL46Z4_SYSTEMTICK_H_
#define _MKL46Z4_SYSTEMTICK_H_

/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4.h"

/*******************************************************************************
   Defination, Macro
*******************************************************************************/

/*!
 * @addtogroup The Registers store the values, what need to show.
 * @{
 */

/** Stacking - Register Layout Typedef */
typedef struct
{
  uint32_t Reserved;
  uint32_t EXC;
  uint32_t R0;
  uint32_t R1;
  uint32_t R2;
  uint32_t R3;
  uint32_t R12;
  uint32_t LR;
  uint32_t Return_Addr;
  uint32_t xPSR;

} STACK_type;

#define STACKING ((STACK_type *)STACK_BASE)

/**
 * @brief This macro used to reate a callback function.
 *
 * @param
 */
typedef void (*Set_SWTimer_Callback)(void);

/*******************************************************************************
  Function Prototype
*******************************************************************************/

/**
 * @brief This Function used to initialize the system tick.
 *
 * @param
 */
void SystemTick_HAL_Init();

/**
 * @brief This Function used to get the address of the function.
 *
 * @param Address of the function to be called.
 */
void SystemTick_HAL_RegisterCallBack(Set_SWTimer_Callback func_name);

#endif /*_MKL46Z4_SYSTEMTICK_HAL_H_*/
