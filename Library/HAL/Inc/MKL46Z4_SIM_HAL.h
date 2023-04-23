/*
********************************************************************************
* @file     MKL46Z4_SIM_HAL.h
* @author   DatTK2
* @version  V1
* @date     29, Dec 2022
******************************************************************************/

#ifndef _MKL46Z4_SIM_HAL_H_
#define _MKL46Z4_SIM_HAL_H_

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
 * @brief This Function used to set System Clock Gating Control Register 5
 *
 * @param Field of System Clock Gating Control Register 5
 */
void SIM_HAL_SCGC5_SetClock(uint8_t SCGC5_field);

/**
 * @brief This Function used to reset System Clock Gating Control Register 5
 *
 * @param Field of System Clock Gating Control Register 5
 */
void SIM_HAL_SCGC5_ResetClock(uint8_t SCGC5_field);

#endif /*_MKL46Z4_SIM_HAL_H_*/
