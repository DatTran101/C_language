/*
*******************************************************************************
* @file    fileHandling.c
* @author  Tran_Khanh_Dat
* @brief   This file contains functions that process the data of the hex file.
*
*******************************************************************************/


/*****************************************************************
 * Include
 ****************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "header.h"
#include <ctype.h>


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

uint8_t hex2U8(char *currentChar)
{
    uint8_t low, high;

    /* Checks for characters in hex and converts them to decimal */
    if (currentChar[0] >= '0' && currentChar[0] <= '9')
    {
        high = currentChar[0] - '0';
    }
    else if (currentChar[0] >= 'a' && currentChar[0] <= 'f')
    {
        high = currentChar[0] - 'a' + 10;
    }
    else if (currentChar[0] >= 'A' && currentChar[0] <= 'F')
    {
        high = currentChar[0] - 'A' + 10;
    }
    else
    {
        /* MISRA standard. */
    }

    if (currentChar[1] >= '0' && currentChar[1] <= '9')
    {
        low = currentChar[1] - '0';
    }
    else if (currentChar[1] >= 'a' && currentChar[1] <= 'f')
    {
        low = currentChar[1] - 'a' + 10;
    }
    else if (currentChar[1] >= 'A' && currentChar[1] <= 'F')
    {
        low = currentChar[1] - 'A' + 10;
    }
    else
    {
        /* MISRA standard. */
    }
    return (((high << 4) & 0xf0) | low);
}

uint16_t hex2U16(char *currentChar)
{
    /* For 16 bit value need to convert 2 times hex2U8 at index 0 and 2 */
    uint8_t high = hex2U8(currentChar);
    uint8_t low = hex2U8(currentChar + 2);
    return (((high << 8) & 0xff00) | low);
}

uint8_t checkSum(t_hexRecord *record)
{
    uint8_t LSB = 0;

    /*  The sum of the decoded byte values. */
    LSB += record->byteCount;
    /* For address with 16 bits, it is necessary to shift 8 bits to the right to calculate the high byte */
    LSB += (record->address >> 8) & 0xff;
    LSB += record->address & 0xff;
    LSB += record->recordType;
    for (uint8_t i = 0; i < record->byteCount; i++)
    {
        LSB += record->data[i];
    }
    return ((~LSB) + 1);
}

uint16_t getLength(char *dataLine)
{
    uint16_t index = 0U;
    uint16_t length = 0U;
    while ((dataLine[index] != '\n') && (dataLine[index] != EOF))
    {
        index++;
    }
    length = index;
    return length;
}

STATUS isValidChar(char *dataLine, uint16_t lengthLine)
{
    uint16_t index = 1U;
    STATUS returnValue = STATUS_OK;
    while ((dataLine[index] != '\0') && (returnValue == STATUS_OK) && index < lengthLine - 1)
    {
        char character = tolower(dataLine[index]);

        /* Check for values outside of hex */
        if (!((character >= '0' && character <= '9') || (character >= 'a' && character <= 'f')))
        {
            returnValue = STATUS_ERROR;
        }
        else
        {
            /* MISRA standard. */
        }

        index++;
    }

    return returnValue;
}

void recordType(uint8_t record)
{
    printf("\n\t[RECORD TYPE]      : ");

    switch (record)
    {
    case 0:
        printf("DATA\n");
        break;
    case 1:
        printf("END OF FILE\n");
        break;
    case 2:
        printf("EXTENDED SEGMENT ADDRESS\n");
        break;
    case 3:
        printf("START SEGMENT ADDRESS\n");
        break;
    case 4:
        printf("EXTENDED LINEAR ADDRESS\n");
        break;
    case 5:
        printf("START LINEAR ADDRESS\n");
        break;
    }
}

HEX_STATUS readHexFile(char *dataLine, t_hexRecord *record)
{
    uint16_t length;
    t_hexRecord recordTemp;
    HEX_STATUS returnValue;

    if ((length = getLength(dataLine)) > 0)
    {

        if (dataLine[START_CODE_INDEX] != ':')
        {
            returnValue = HEX_MISSING_START_CODE;
        }
        else if (isValidChar(dataLine, length) != STATUS_OK)
        {
            returnValue = HEX_INVALID_CHARACTER;
        }
        else
        {
            /* Calculate the decoded byte count */
            recordTemp.byteCount = hex2U8(dataLine + BYTE_COUNT_INDEX);
            if (length < (LENGTH_0_CONTAIN_DATA + recordTemp.byteCount * 2))
            {
                returnValue = HEX_INVALID_LENGTH;
            }
            else
            {
                /* Calculate the decoded address */
                recordTemp.address = hex2U16(dataLine + ADDRESS_INDEX);

                /* Calculate the decoded record type */
                recordTemp.recordType = hex2U8(dataLine + RECORD_TYPE_INDEX);

                uint16_t index;

                /* Calculate the decoded data */
                for (index = 0U; index < recordTemp.byteCount; index++)
                {
                    recordTemp.data[index] = hex2U8(dataLine + DATA_INDEX + 2 * index);
                }

                /*  The sum of the decoded byte values */
                recordTemp.checkSum = hex2U8(dataLine + LENGTH_0_CONTAIN_DATA - 2 + recordTemp.byteCount * 2);

                *record = recordTemp;

                if (recordTemp.checkSum != checkSum(&recordTemp))
                {
                    returnValue = HEX_ERROR_CHECKSUM;
                }
                else
                {
                    returnValue = HEX_OK;
                }
            }
        }
    }
    else
    {
        returnValue = HEX_EOF;
    }

    return returnValue;

}

STATUS checkCharacter(char *request)
{
    STATUS retVal;

    fflush(stdin);

    /* Return true if input value valid */
    if ((1 == scanf("%c", request)) && (getchar() == '\n'))
    {
        retVal = STATUS_OK;
    }
    else
    {
        retVal = STATUS_ERROR;
    }

    return retVal;

}