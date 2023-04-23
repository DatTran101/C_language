/*
*******************************************************************************
* @file    HAL.c
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions prototypes for the HAL
*	       module driver
*******************************************************************************/

#include "HAL.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/

static FILE *sp_file = NULL;
static uint32_t s_sectorSize = 0U;


/*******************************************************************************
* Code
******************************************************************************/

bool kmc_init(const uint8_t* const filePath)
{

    /* Initialize pointer for file
     * Check Pointer, if pointer null is return false
     * Assign size 512 for static variable
     */

    bool result = true;
    sp_file = fopen(filePath, "rb");

    if(sp_file == NULL)
    {
        result = false;
    }
    else
    {
        s_sectorSize = NUMBER_OF_BYTE_PER_SECTOR;
    }

    return result;
}

int32_t kmc_read_sector(const uint32_t index, uint8_t* const buff)
{

    /* Initialize variable of number of byte which received for fread
     * Check function fseek have do successful, and pick at index need to read
     * Assign pointer at set position
     */

    size_t numberOfByte = 0U;

    if(fseek(sp_file, (index * s_sectorSize), SEEK_SET) == 0U)
    {
        numberOfByte = fread(buff, 1U, (size_t)s_sectorSize, sp_file);
        if(numberOfByte != s_sectorSize)
        {
            numberOfByte = 0U;
        }
    }

    return (int32_t)numberOfByte;
}

int32_t kmc_read_multi_sector(const uint32_t index, const uint32_t num, uint8_t* const buff)
{
    /* Return value of byte which have read */
    size_t numberOfByte = 0U;
    /* Count byte number when read multi sector */
    size_t numberOfByteTemp = 0U;
    /* offset of buffer */
    uint64_t offset = 0U;
    /* Count number sector */
    uint32_t count = 0U;

    if(fseek(sp_file, index * s_sectorSize, SEEK_SET) == 0U)
    {
        for (count = 0U; count < num; count++)
        {
            offset = count * s_sectorSize;
            numberOfByteTemp += fread(&buff[offset], 1U, (size_t)s_sectorSize, sp_file);
        }
        if(numberOfByteTemp == ((size_t)num * s_sectorSize))
        {
            numberOfByte = numberOfByteTemp;
        }
    }
    return (int32_t)numberOfByte;
}

bool kmc_deinit(void)
{
    bool result = true;

    if (fclose(sp_file) == 0U)
    {
        sp_file = NULL;
    }
    else
    {
        result = false;
    }

    return result;
}
