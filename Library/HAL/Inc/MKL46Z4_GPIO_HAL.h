/*
********************************************************************************
* @file     MKL46Z4_GPIO_HAL.h
* @author   DatTK2
* @version  V1
* @date     31, Dec 2022
*******************************************************************************/

#ifndef _MKL46Z4_GPIO_HAL_H_
#define _MKL46Z4_GPIO_HAL_H_


/*******************************************************************************
  Includes
*******************************************************************************/

#include <stdint.h>
#include "MKL46Z4.h"



/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

typedef enum
{
  RESET = 0,
  SET = 1,
} PINx_State_e;


/*******************************************************************************
* Global variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief This Function used to config Pin is output.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: Position of corresponding pin.
 */
void GPIO_HAL_Config_Output(GPIO_Type *GPIOx, uint8_t PINx);

/**
 * @brief This Function used to config Pin is high level output.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: Position of corresponding pin.
 */
void GPIO_HAL_Write1Pin(GPIO_Type *GPIOx, uint8_t PINx, PINx_State_e state);

/**
 * @brief This Function used to config Pin is tongle output.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: Position of corresponding pin.
 */
void GPIO_HAL_Toggle(GPIO_Type *GPIOx, uint8_t PINx);

/**
 * @brief This Function used to config Pin is input.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: Position of corresponding pin.
 */
void GPIO_HAL_Config_Input(GPIO_Type *GPIOx, uint8_t PINx);

/**
 * @brief This Function used to Read  value of corresponding pin and return
 * this value.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: Position of corresponding pin.
 */
uint8_t GPIO_HAL_Read_PIN(GPIO_Type *GPIOx, uint8_t PINx);

#endif /*_MKL46Z4_GPIO_HAL_H_*/
