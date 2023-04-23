/*
********************************************************************************
* @file     MKL46Z4_PIT_HAL.h
* @author   DatTK2
* @version  V1
* @date     15, Jan 2023
*******************************************************************************/

#ifndef __MKL46Z4_PIT_HAL_H__
#define __MKL46Z4_PIT_HAL_H__

/*******************************************************************************
   Defination, Macro
*******************************************************************************/

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
typedef void (*PIT_DRV_CallBack)(void);

/*******************************************************************************
  Function Prototype
*******************************************************************************/

/**
 * @brief This Function used to initialize the PIT.
 *
 * @param
 */
void PIT_HAL_Init(void);

/**
 * @brief This Function used to disable the PIT.
 *
 * @param
 */
void PIT_HAL_Disable(void);

/**
 * @brief This Function used to get the address of the function.
 *
 * @param Address of the function to be called.
 */
void PIT_HAL_RegisterCallback(PIT_DRV_CallBack func_name);

/**
 * @brief Deinitialize PIT exception request
 */
void PIT_HAL_Deinit(void);

#endif /*_MKL46Z4_PIT_HAL_H_*/
