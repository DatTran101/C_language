/********************************************************************************
* @file    arrayInOut.h
* @author  Tran_Khanh_Dat.
* @brief   This file processes the input data and outputs the required data.
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"
#include <stdint.h>


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside :
* Prototypes
******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

void autoArrayGen(uint32_t integerArray[], uint8_t arrayLength)
{
    printf("---------------------------------------------Arrays are automatically allocated-----------------------------------------\n\n");
    for (uint32_t i = 0; i < arrayLength; i++)
    {
        printf("|integerArray[%d] = ", i);
        integerArray[i] = rand();
        printf("%d\n", integerArray[i]);
    }
}
void manualArrayGen(uint32_t integerArray[], uint8_t arrayLength)
{
    printf("---------------------------------------------Arrays are manually allocated----------------------------------------------\n\n");
    for (uint32_t i = 0; i < arrayLength; i++)
    {
        printf("|integerArray[%u] = ", i);
        while (!isValidValue(&integerArray[i]))
        {
            /*  Enter the values of each array element. */
            fflush(stdin);
            printf("|!Incorrect array element value entered! Please Re-Enter !\n");
            printf("|integerArray[%u] = ", i);
        }
    }
}
uint8_t enterArrayLength()
{
    uint32_t arrayLength;
    printf("|Enter the number of array elements[0, 100]: ");
    while (!isValidValue(&arrayLength) || 0 > arrayLength || arrayLength > 100)
    {

        /* Enter the number of elements of the array. */
        fflush(stdin); // Clear cache
        printf("|Wrong number of arrays entered\n");
        printf("|Please re-enter the number of array elements\n");
        printf("|Enter the number of array elements[0, 100]: ");
    }
    return arrayLength;
}

uint8_t arrayInitMethod()
{
    uint32_t manualOrAutomatic;

    printf("|Enter the array initialization method:\n");
    printf("|Enter '1' to initialize the array manually\n");
    printf("|Enter '2' to initialize the array automatically\n");
    while (!(isValidValue(&manualOrAutomatic) && (manualOrAutomatic == 2 || manualOrAutomatic == 1)))
    {
        printf("|!Wrong method entered ! Please re-enter !\n");
        fflush(stdin);
        printf("|Enter the array initialization method:\n");
        printf("|Enter '1' to initialize the array manually\n");
        printf("|Enter '2' to initialize the array automatically\n");
        fflush(stdin);
    }
    return manualOrAutomatic;
}
void arrayInitialization(uint32_t integerArray[], uint8_t *arrayLength)
{
    printf("---------------------------------------------CREATE ARRAY OF INTEGERS---------------------------------------------------\n\n");
    /* If array already exists, set all elements to 0. */
    if (*arrayLength > 0)
    {
        for (uint32_t i = 0; i < *arrayLength; i++)
        {
            integerArray[i] = 0;
        }
    }
    /* Enter array length. */
    *arrayLength = enterArrayLength();
    if (1 == arrayInitMethod())
    {
        manualArrayGen(integerArray, *arrayLength);
    }
    else
    {
        autoArrayGen(integerArray, *arrayLength);
    }
    printf("\n");
}
bool checkEmptyArray(uint32_t integerArray[], uint8_t arrayLength)
{
    bool retVal = true;
    for (uint32_t i = 0; i < arrayLength; i++)
    {
        /* If the elements of array are all 0, then the array is empty. */
        if (integerArray[i] != 0)
        {
            retVal = false;
            break;
        }
    }
    return retVal;
}
void outputArray(uint32_t integerArray[], uint8_t arrayLength)
{
    printf("---------------------PRINT ARRAY OF INTEGERS--------------------------\n\n");

    /* Check if array is empty or not then message. */
    if (arrayLength == 0 || checkEmptyArray(integerArray, arrayLength))
    {
        printf("|!Empty array!");
    }
    else
    {
        printf("|Elements of the integer array:\n");
        /* Print elements of the integer array on a row. */

        for (int i = 0; i < arrayLength; i++)
        {
            printf("%d\t", integerArray[i]);
        }
    }
    printf("\n\n");
}
