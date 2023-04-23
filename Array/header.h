
/*
*******************************************************************************
* @file    header.h
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions prototypes
*******************************************************************************/

#ifndef _HEADER_H_
#define _HEADER_H_
#include <stdbool.h>
#include <stdint.h>


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

/*
The Menu function contains the program options
*/
void menu();

/*
Check whether the input value is valid or not
true if valid
false if not valid
*/
bool isValidValue(uint32_t *value);

/*
Check whether the input character is valid or not
true if valid
false if not valid
*/
bool isValidCharacter(char *selectMenu);

/*
Automatic array initialization
With the input parameter as:
   Array of uint32_tegers
   The number of elements of the array
The value of the array elements will be initialized randomly using the rand() function.
*/
void autoArrayGen(uint32_t integerArray[], uint8_t arrayLength);

/*
Manual array initialization
With the input parameter as:
   Array of uint32_tegers
   The number of elements of the array
The value of the array elements will be initialized manually by the user input.
*/
void manualArrayGen(uint32_t integerArray[], uint8_t arrayLength);

/*
Enter array length with return type as array length
*/
uint8_t enterArrayLength();

/*
Create two array initializers automatic and manual with return type is the initialization method
*/
uint8_t arrayInitMethod();

/*
Array initialization
Parameters passed in:
    uint32_teger array
    The number of elements of the array
If the array already has a value, delete the data of the old array.
*/
void arrayInitialization(uint32_t integerArray[], uint8_t *arrayLength);

/*
Check if array is empty or not
true if the array is empty
false if the array contains values
*/
bool checkEmptyArray(uint32_t integerArray[], uint8_t arrayLength);

/*
Pruint32_t the elements of an array of uint32_tegers
Parameters passed in:
    uint32_teger array
    The number of elements of the array
If the array does not have a value, the array is empty.
*/
void outputArray(uint32_t integerArray[], uint8_t arrayLength);

/*
Enter Kth position you want to insert
*/
void enterKPosition(uint32_t integerArray[], uint8_t kthPosition, uint8_t arrayLength);

/*
Enter array value at Kth Position you want to insert
*/
void enterArrayValueAtKPosition(uint32_t integerArray[], uint8_t kthPosition);

/*
Add an element to the kth position in array
Parameters passed in:
    uint32_teger array
    The number of elements of the array
    The kth position you want to insert
If the input k value is not valid, it is requested to re-enter it.
*/
void insertAtKPosition(uint32_t integerArray[], uint8_t *arrayLength, uint8_t insertKthPosition);

/*
Remove element at kth position in array
Parameters passed in:
    uint32_teger array
    The number of elements of the array
    The kth position you want to delete
If the input k value is not valid, it is requested to re-enter it.
*/
void deleteAtKPosition(uint32_t integerArray[], uint8_t *arrayLength, uint32_t insertKthPosition);

/*

*/
void deleteArrayValueAtKPosition(uint32_t integerArray[], uint8_t *arrayLength, uint32_t kthPosition);
/*
Swap two numbers together
The input parameter is the two numbers you want to swap.
*/
void swap(uint32_t *left, uint32_t *right);

/*
Check if left value is greater than right value
Aim to swap to sort ascending.
*/
bool ascending(uint32_t left, uint32_t right);

/*
Check if left value is less than right value
Aim to swap to sort descending.
*/
bool descending(uint32_t left, uint32_t right);

/*
Sort the array in ascending or descending order based on the input parameter compareFunction.
The compareFunction function will call one of the two
ascending functions to sort ascending or descending to sort descending
The remaining input parameters are::
    uint32_teger array
    The number of elements of the array
*/
void selectionSort(uint32_t integerArray[], uint8_t arrayLength, bool compareFunction(uint32_t, uint32_t));

/*
Ascending sort
*/
void ascendingSort(uint32_t integerArray[], uint8_t arrayLength, bool compareFunction(uint32_t, uint32_t));

/*
Descending sort
*/
void descendingSort(uint32_t integerArray[], uint8_t arrayLength, bool compareFunction(uint32_t, uint32_t));

/*
Check if x exists in array or not? Return:
true if yes
false if not exist
*/
bool checkExistenceValueX(uint32_t integerArray[], uint8_t arrayLength, uint32_t finduint32_tegerX);

/*
Enter X value you want to find
*/
void enterXValue(uint32_t *finduint32_tegerX);

/*
Find if x value exists in element or not?
Parameters passed:
    uint32_teger array
    Number of elements of the array
    Value x want to check
*/
void findX(uint32_t integerArray[], uint8_t arrayLength, uint32_t finduint32_tegerX);

#endif
