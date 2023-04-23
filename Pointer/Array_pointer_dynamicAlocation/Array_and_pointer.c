
/*
*******************************************************************************
* @file    task3.c
* @author  Tran_Khanh_Dat
* @brief   The program enters two integers.
*          Checking if they are correct requires 8bit integers.
*          Store them in the array.
*          Calculates the absolute value of the difference between two elements of an array.
*
*******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
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

/* Declare a,b of type int to check oil condition. */
static int a = 0;
static int b = 0;

/* Abs_sub holds the result of the calculation |a-b|. */
static uint8_t abs_sub = 0;

/* Array that stores 2 positive 8-bit integers entered from the keyboard. */
static uint8_t array[2] = {0};

/* Absolute value function a-b. */
void absolute_value(uint8_t *data);

/* Input function from the keyboard 2 numbers a and b. */
void enter_value(int *a, int *b);

/* The function displays 2 entered numbers with 8-bit positive integer type. */
void show_value();


/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    char option = '0';
    do
    {
        enter_value(&a, &b);

        /* Put values a, b into array to prepare to pass to absolute_value function. */
        array[0] = a;
        array[1] = b;

        show_value();
        absolute_value(array);

        printf("Result of abs(a-b): %d\n", abs_sub);
        printf("Press y to continue, press anykey to stop:");

        scanf("%c", &option);
        if('y' != option)
        {
            printf("\n-----Finish! Thank you very much!-----\n");
        }
    } while ('y' == option);
    return 0;
}

void enter_value(int *a, int *b)
{
    uint8_t condition = 0;
    printf("Enter value:\n");
    do
    {
        printf("a = ");
        condition = 0;

        /* The variable is_valid_ui8 receives the true or false result of the scanf function. */
        bool is_valid_ui8 = scanf("%d", a);

        if(is_valid_ui8 != true | getchar() != '\n' | *a <= 0 | *a > 255 )
        {
            printf("Please enter interger type and 0 < a < 256 !\n");
            condition =  true;
        }
    } while ( true == condition );

    do
    {
        printf("b = ");

        condition = 0;

        /* The variable is_valid_ui8 receives the true or false result of the scanf function. */
        bool is_valid_ui8 = scanf("%d", b);

        if(is_valid_ui8 != true | getchar() != '\n' | *b <= 0 | *b > 255 )
        {
            printf("Please enter interger type and 0 < b < 255!\n");
            condition =  true;
        }
    } while ( 1 == condition );
}

void show_value()
{
    printf("\nThe value that entered: a = %d\t b = %d\n", array[0], array[1]);
}

void absolute_value(uint8_t *data)
 {
    abs_sub = abs(*(data) - *(data+1) );
 }





