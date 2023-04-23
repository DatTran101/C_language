#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/*******************************************************************************
 * Code
 ******************************************************************************/

void menu()
{
    system("cls");
    printf("+-------------------------------------------------------------------+\n");
    printf("|Enter the request you want to make                                 |\n");
    printf("|Enter 'c' to create an array of integers                           |\n");
    printf("|Enter 'p' to print the array                                       |\n");
    printf("|Enter 'i' to add 1 element to the kth position of the array        |\n");
    printf("|Enter 'd' to delete 1 element at the kth position in the array     |\n");
    printf("|Enter 's' to sort the array in ascending order                     |\n");
    printf("|Enter 'x' to sort the array in descending order                    |\n");
    printf("|Enter 't' to search if a number exists in the array?               |\n");
    printf("|Enter 'e' to exit the program                                      |\n");
    printf("+-------------------------------------------------------------------+\n");

    fflush(stdin);
}
