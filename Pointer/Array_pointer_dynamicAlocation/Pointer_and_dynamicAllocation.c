/*
*******************************************************************************
* @file    task2.c
* @author  Tran_Khanh_Dat
* @brief   The program learns about how 2-level pointers and 1-level pointers work.
*          And learn how pointers work with dynamic memory allocation.
*
*******************************************************************************/

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>


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


bool allocate10Bytes(uint8_t **outPtr)
{
  *outPtr = (uint8_t*)calloc(10, sizeof(uint8_t));

  printf("\nAllocated memory address: %p", *outPtr);

  if(*outPtr != NULL)
  {
    printf("\nAllocation is success: ");
    return true;
  }
  else
  {
    printf("\nAllacation is fail:");
    return false;
  }
}


/*******************************************************************************
 * Code
 ******************************************************************************/

int main ()
{
  uint8_t *myPtr = NULL;
  bool res = allocate10Bytes (&myPtr);

  printf("\nResult returned: %d ", res);
  printf("\nThe address the pointer myptr is pointing: %p\n", myPtr);

  free(myPtr);

  return 0;
}
