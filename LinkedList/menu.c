/*
*******************************************************************************
* @file    menu.c
* @author  Tran_Khanh_Dat
* @brief   This file is used to handle user selections
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/
static Collection linkedList;


/*******************************************************************************
 * Code
 ******************************************************************************/

void menu()
{
    system("cls");
    printf("******************************Program to manage arrays using Linked List******************************\n");
    printf("|\t\tEnter the request you want to make                                                   |\n");
    printf("|\t\tEnter 'i' to initialize Linked List                                                  |\n");
    printf("|\t\tEnter 'c' to delete Linked List                                                      |\n");
    printf("|\t\tEnter 'a' to add an element to a Linked List                                         |\n");
    printf("|\t\tEnter 'p' to print Linked List                                                       |\n");
    printf("|\t\tEnter 'd' to delete the element containing the value k entered from the keyboard     |\n");
    printf("|\t\tEnter 'f' to search for the position of the value k in the Linked List               |\n");
    printf("|\t\tEnter 's' to sort ascending in Linked List                                           |\n");
    printf("|\t\tEnter 'x' to sort descending in Linked List                                          |\n");
    printf("|\t\tEnter 'e' to exit program                                                            |\n");
    printf("******************************************************************************************************\n");
}
STATUS actions()
{
    STATUS retVal = STATUS_OK;
    char request;
    while (isValidChar(&request) != STATUS_OK)
    {
        system("cls");
        printf("|!The character you entered is not valiD!\n");
        /* Clear the cache to not skip commands system("pause") */
        fflush(stdin);
        system("pause");
        menu();
    }
    system("cls");
    switch (request)
    {
    case 'i':
        initializeLinkedList(&linkedList);
        system("pause");
        break;
    case 'c':
        if (STATUS_OK != deleteLinkedList(&linkedList))
        {
            printf("List does not exist\n");
        }
        system("pause");
        break;
    case 'a':
        addElement(&linkedList);
        break;
    case 'p':
        if (STATUS_OK != printList(&linkedList))
        {
            printf("List does not exist\n");
        }
        system("pause");
        break;
    case 'd':
        deleteElement(&linkedList);
        break;
    case 'f':
        search(&linkedList);
        break;
    case 's':
        ascendingSort(&linkedList, ascending);
        break;
    case 'x':
        descendingSort(&linkedList, descending);
        break;
    case 'e':
        retVal = STATUS_ERROR;
        break;
    default:
        system("cls");
        printf("|!The character you entered is not valiD!\n");
        system("pause");
        break;
    }
    system("cls");
    return retVal;
}