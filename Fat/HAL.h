/********************************************************************************
* @file    HAL.h
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions prototypes for the HAL
*	       module driver
*******************************************************************************/

#ifndef _HAL_H_
#define _HAL_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define NUMBER_OF_BYTE_PER_SECTOR (512U)

/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/* Initialize pointer file and size of sector. */
/* Paramater: Pointer of file. */
/* Return value true or false. */
bool kmc_init(const uint8_t* const filePath);

/* Read number bytes in one sector. */
/* Paramater 1: Sector need to access. */
/* Paramater 2: Buffer need to store. */
/* Return value: bytes were read. */
int32_t kmc_read_sector(const uint32_t index, uint8_t* const buff);

/* Read number bytes of multi sectors. */
/* Paramater 1: Start sector. */
/* Paramater 2: Number of sector need to read. */
/* Paramater 3: Buffer need to store. */
/* Return value: bytes were read. */
int32_t kmc_read_multi_sector(const uint32_t index, const uint32_t num, uint8_t* const buff);

/* Close file. */
/* Return value true or false. */
bool kmc_deinit(void);

#endif