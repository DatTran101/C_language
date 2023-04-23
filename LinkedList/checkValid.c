/********************************************************************************
* @file    checkValid.c
* @author  Tran_Khanh_Dat
* @brief   This file is used to check whether the input data meets
*          the requirements or not.
*******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "header.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

STATUS isValidUi32(uint32_t *value)
{
    STATUS retVal;
    /* Clear cache*/
    fflush(stdin);
    if ((1 == scanf("%u", value)) && (getchar() == '\n'))
    {
        retVal = STATUS_OK;
    }
    else
    {
        retVal = STATUS_ERROR;
    }
    return retVal;
}
STATUS isValidChar(char *request)
{
    STATUS retVal;
    fflush(stdin);
    /* Return true if input value valid. */
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