/********************************************************************************
* @file    arrayHandling.h
* @author  Tran_Khanh_Dat
* @brief   This file handles user selections
*******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include "header.h"


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

bool isValidValue(uint32_t *value)
{
    fflush(stdin);
    /* Return true if input value valid. */
    return ((1 == scanf("%u", value)) && (getchar() == '\n'));
}
bool isValidCharacter(char *selectMenu)
{
    fflush(stdin);
    /* Return true if input value valid. */
    return ((1 == scanf("%c", selectMenu)) && (getchar() == '\n'));
}

bool checkExistenceValueX(uint32_t integerArray[], uint8_t arrayLength, uint32_t finduint32_tegerX)
{
    bool retVal = false;
    for (uint32_t i = 0; i < arrayLength; i++)
    {
        /* If there exists a value x in the array, return true to terminate the function. */
        if (integerArray[i] == finduint32_tegerX)
        {
            retVal = true;
            break;
        }
    }
    return retVal;
}

void enterXValue(uint32_t *finduint32_tegerX)
{
    printf("|Enter the value x you want to check:");
    while (!isValidValue(finduint32_tegerX))
    {
        printf("|!The value of X entered is not valid! Please Re-Enter !\n");
        printf("|Enter the value x you want to check:");
        fflush(stdin);
    }
}

void findX(uint32_t integerArray[], uint8_t arrayLength, uint32_t finduint32_tegerX)
{
    printf("---------------------------------------------CHECKING THE EXISTENCE OF VALUES X IN ARRAYS-------------------------------\n\n");
    if (arrayLength == 0)
    {
        printf("|!Empty array! Please initialize the array!\n");
    }
    else
    {
        enterXValue(&finduint32_tegerX);

        /* Check if x exists to pruint32_t the message to the screen. */
        if (checkExistenceValueX(integerArray, arrayLength, finduint32_tegerX))
        {
            printf("|Number %d exist in array\n\n", finduint32_tegerX);
        }
        else
        {
            printf("|Number %d does not exist in array\n\n", finduint32_tegerX);
        }
    }
}

void enterKPosition(uint32_t integerArray[], uint8_t kthPosition, uint8_t arrayLength)
{
    printf("|Enter the kth position: ");
    while (!isValidValue(&integerArray[kthPosition]) || (kthPosition > arrayLength) || (kthPosition < 0))
    {
        printf("|!The kth position has no molecule or you entered it wrong! Please re-enter !\n");
        printf("|Enter the kth position: ");
        /* Clear cache. */
        fflush(stdin);
    }
}

void enterArrayValueAtKPosition(uint32_t integerArray[], uint8_t kthPosition)
{
    while (!isValidValue(&integerArray[kthPosition]))
    {
        /* Enter the value you want to insert at the kth element of the array. */
        fflush(stdin);
        printf("|!Incorrect array element value entered! Please Re-Enter!\n");
        printf("|Enter the value of the %dth element: ", kthPosition);
    }
}

void insertAtKPosition(uint32_t integerArray[], uint8_t *arrayLength, uint8_t kthPosition)
{
    printf("---------------------------------------------ADD A VALUE TO THE Kth POSITION--------------------------------------------\n\n");
    if (*arrayLength == 100)
    {
        printf("|!Array is full! You can't add value anymore!\n");
    }
    else
    {
        if (*arrayLength == 0)
        {
            printf("|Empty array, You can only add to the first element of the array\n");
            kthPosition = 0;
        }
        else
        {
            enterKPosition(&integerArray[kthPosition], kthPosition, *arrayLength);
        }

        /* The number of network elements is increased by 1. */
        (*arrayLength)++;

        for (uint32_t i = *arrayLength - 1; i > kthPosition; i--)
        {
            /* Move molecules starting from the kth position to the (k + 1)th position. */
            integerArray[i] = integerArray[i - 1];
        }
        printf("|Enter the value of the %dth element: ", kthPosition);
        enterArrayValueAtKPosition(integerArray, kthPosition);
    }
    printf("\n");
}

void deleteAtKPosition(uint32_t integerArray[], uint8_t *arrayLength, uint32_t kthPosition)
{
    {
        for (uint32_t i = kthPosition; i < *(arrayLength)-1; i++)
        {
            /* Insert the (i + 1)th elements down to the ith element. */
            integerArray[i] = integerArray[i + 1];
        }
        /* Reduce the number of array elements. */
        --(*arrayLength);
    }
    printf("\n");
}

void deleteArrayValueAtKPosition(uint32_t integerArray[], uint8_t *arrayLength, uint32_t kthPosition)
{
    printf("---------------------------------------------DELETE A VALUE AT THE Kth POSITION-----------------------------------------\n\n");
    if (*arrayLength == 0)
    {
        printf("|!Empty array! Please initialize the array!\n");
    }
    else
    {
        enterKPosition(&integerArray[kthPosition], kthPosition, *arrayLength);
        deleteAtKPosition(integerArray, arrayLength, kthPosition);
    }
}

void swap(uint32_t *left, uint32_t *right)
{
    /* Use an uint32_termediate memory variable to swap 2 values. */
    uint32_t temp = *left;
    *left = *right;
    *right = temp;
}

bool ascending(uint32_t left, uint32_t right)
{
    /* Returns true if the value on the left is greater than the value on the right. */
    return left > right;
}

bool descending(uint32_t left, uint32_t right)
{
    /* Returns true if the value on the left is less than the value on the right. */
    return left < right;
}

void selectionSort(uint32_t integerArray[], uint8_t arrayLength, bool compareFunction(uint32_t, uint32_t))
{
    for (uint32_t i = 0; i < arrayLength - 1; i++)
    {
        /* Get the elements behind and compare with the previous element. */
        for (uint32_t j = i + 1; j < arrayLength; j++)
        {
            /* Call ascending or descending to sort ascending or descending. */
            if (compareFunction(integerArray[i], integerArray[j]))
            {
                swap(&integerArray[i], &integerArray[j]);
            }
        }
    }
}

void ascendingSort(uint32_t integerArray[], uint8_t arrayLength, bool compareFunction(uint32_t, uint32_t))
{
    printf("---------------------------------------------SORT ARRAY IN ASCENDING ORDER----------------------------------------------\n\n");
    if (arrayLength == 0)
    {
        printf("|!Empty array! Please initialize the array!\n");
    }
    else
    {
        selectionSort(integerArray, arrayLength, ascending);
        printf("|Array is sorted ascending\n\n");
    }
}

void descendingSort(uint32_t integerArray[], uint8_t arrayLength, bool compareFunction(uint32_t, uint32_t))
{
    printf("---------------------------------------------SORT ARRAY IN DESCENDING ORDER---------------------------------------------\n\n");
    if (arrayLength == 0)
    {
        printf("|!Empty array! Please initialize the array!\n");
    }
    else
    {
        selectionSort(integerArray, arrayLength, descending);
        printf("|Array is sorted Descending\n\n");
    }
}