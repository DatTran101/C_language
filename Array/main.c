/*
*******************************************************************************
* @file    main.c
* @author  Tran_Khanh_Dat
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "header.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define MAX 100


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

int main(void)
{
    /* Variable containing menu choices */
    char selectMenu;

    uint32_t integerArray[MAX] = {0};

    /* Number of elements initially empty */
    uint8_t arrayLength = 0;

    /* The Kth position you want to insert or delete in the array */
    uint8_t kthPosition = 0;

    /* Integer x wants to check for existence */
    uint32_t findIntegerX;

    do
    {
        menu();
        while (!isValidCharacter(&selectMenu))
        {
            system("cls");
            printf("|!The character you entered is not valiD!\n");

            /* Clear the cache to not skip commands system("pause") */
            fflush(stdin);

            system("pause");
            menu();
        }

        system("cls");
        switch (selectMenu)
        {

            case 'c':
                arrayInitialization(integerArray, &arrayLength);
                system("pause");
                break;

            case 'p':
                outputArray(integerArray, arrayLength);
                system("pause");
                break;

            case 'i':
                insertAtKPosition(integerArray, &arrayLength, kthPosition);
                system("pause");
                break;

            case 'd':
                deleteArrayValueAtKPosition(integerArray, &arrayLength, kthPosition);
                system("pause");
                break;

            case 's':
                ascendingSort(integerArray, arrayLength, ascending);
                system("pause");
                break;

            case 'x':
                descendingSort(integerArray, arrayLength, descending);
                system("pause");
                break;

            case 't':
                findX(integerArray, arrayLength, findIntegerX);
                system("pause");
                break;

            case 'e':
                printf("---------------------!YOU HAVE EXITED THE PROGRAM!---------------------\n");
                break;

            default:
                printf("|!The character you entered is not valiD!\n\n");
                system("pause");
                break;
        }

    } while (selectMenu != 'e');

    return 0;
}
