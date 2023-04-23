
/*
*******************************************************************************
* @file    task1.c
* @author  Tran_Khanh_Dat
* @brief   Program to input from the keyboard n 8-bit positive integers.
*          Check whether the input conditions are correct or not.
*          Print the entered value along with the allocation address for that value.
*          Print to the screen the address that is carrying the maximum value.
*
*******************************************************************************/


#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>

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

/* The function allows the user to enter the number of elements from the keyboard. */
int  enter_number_of_elements(void);

/* Function to check input conditions. */
bool is_valid_int(int *number_element);

/* Function to enter values for elements. */
void enter_value(int number_element, int *aptr);

/* The function displays the value of the element and the address of the corresponding
element in reverse order of entry.*/
void show_result(int number_element, int *aptr);

/* The function has the return value as the address of the element with the largest value,
helping the bptr pointer to manage that address */
int  *manage_addr_of_max_value(int number_element, int *aptr);


/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    int *bptr = NULL;
    char option = '0';
    do
    {
       int number_element = enter_number_of_elements();

        /* Dynamic allocation of pointers aptr. */
        int* aptr = (int*)calloc(number_element, sizeof(uint16_t));

        enter_value(number_element, aptr);
        show_result(number_element, aptr);

        /* The pointer bptr is pointing to the address of the element with the largest value. */
        bptr = manage_addr_of_max_value(number_element, aptr);

        free(aptr);

        printf("\nPress y to continue, press anykey to stop:");
        scanf("%c", &option);
        printf("\n");
        if('y' != option)
        {
            printf("------Finish! Thank you very much!-----\n");
        }
    } while ('y' == option);

    return 0;
}

int enter_number_of_elements()
{
    int number = 0;
    bool result = false;

    do
    {
        printf("Enter the number of element 0 < number_element < 256: ");
        result = is_valid_int(&number);
    } while (0 == result | number <= 0 | number > 255);

    return number;
}

bool is_valid_int(int *number_element)
{
    bool result  = false;
    if(scanf("%d", number_element)!=1 | getchar() != '\n' )
    {
        printf("Please enter interger type!\n");
        result = false;
    }
    else
    {
        result = true;
    }
    return result;
}

void enter_value(int number_element, int *aptr)
{
    int index = 0;
    bool result = false;

    printf("Enter the value of elements!\n");
    printf("***** NOTE ***** (0 < value <= 65 535):\n");

    for(index = 1; index <= number_element; index ++)
    {
        do
        {
        printf("value%d = ", index);
        result = is_valid_int(aptr+index);
        } while (false == result | (*(aptr + index)) <= 0 | (*(aptr + index)) >= 65535);
    }
}

void show_result(int number_element, int *aptr)
{
    int index = 0;

    printf("\nThe address of element and the value of element that you entered: ");
    printf("\nFormat: <Address>:       <Value>\n");

    for(index = number_element; index > 0; index --)
    {
        printf("\t%p: %d", (aptr + index), *(aptr + index));
        printf("\n");
    }
}

int *manage_addr_of_max_value(int number_element, int *aptr)
{
    int max = 0;
    int index =0;
    int *bptr = NULL;
    max = *aptr;
    bptr = aptr;

    /* Find the element with the largest value and the corresponding address. */
    for(index = 1; index <= number_element; index ++)
    {
        if(*(aptr +index)>max)
        {
            max = *(aptr + index);
            bptr = (aptr + index);
        }
        else continue;
    }

    /* Print the results to check if the results are correct. */
    printf("\nThe adress and max value:");
    printf("\nFormat: <Address>:        <Value>\n");
    printf("\t%p: %d\n", bptr, max);

    return bptr;
}


