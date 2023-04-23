/*
********************************************************************************
* @file     MKL46Z4_PORT_HAL.h
* @author   DatTK2
* @version  V1
* @date     30, Dec 2022
******************************************************************************/

#ifndef _MKL46Z4_PORT_HAL_H_
#define _MKL46Z4_PORT_HAL_H_

/*******************************************************************************
  Includes
*******************************************************************************/

#include <stdint.h>
#include "MKL46Z4.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief This Function used to enable MUX field of Pin Control Register
 *
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what starting position of corresponding field.
 * Param3: Status of corresponding field or mode of corresponding.
 */
void PORT_HAL_EnableMUX(PORT_Type *PORTx, uint8_t PINx, uint8_t status);

/**
 * @brief This Function used to disable MUX field of Pin Control Register
 *
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what starting position of MUX field.
 */
void PORT_HAL_DisableMUX(PORT_Type *PORTx, uint8_t PINx);

/**
 * @brief This Function used to disable "pull enable" field of
 * Pin Control Register.
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what position of pull selection field.
 */
void PORT_HAL_EnablePull(PORT_Type *PORTx, uint8_t PINx);

/**
 * @brief This Function used to disable "pull enable" field of
 * Pin Control Register.
 *
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what position of pull field.
 */
void PORT_HAL_DisablePull(PORT_Type *PORTx, uint8_t PINx);

/**
 * @brief This Function used to config pullup internal resistor.
 *
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what position of pull select field.
 */
void PORT_HAL_PullUp(PORT_Type *PORTx, uint8_t PINx);

/**
 * @brief This Function used to config pulldown internal resistor.
 *
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what position of pull select field.
 */
void PORT_HAL_PullDown(PORT_Type *PORTx, uint8_t PINx);

#endif /*_MKL46Z4_PORT_HAL_H_*/