#include "header.h"
#include <stdio.h>
#include <stdbool.h>


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define MAX_LEN 20


/*******************************************************************************
* Variables
******************************************************************************/

static status_enum_t isCorrect;
static uint16_t numOfAccount = 1;
static char input = 'a';


/*******************************************************************************
* Add static API prototype in C file inside :
* Prototypes
******************************************************************************/

/* The function is used to input an array of characters from the keyboard. */
static uint8_t enterArray(char *pArray);

/* The function used to clear the cache. */
static void clear_stdin();

/* The function is used to allow the user to continue the program or exit. */
static void option();


/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    uint8_t strLen = 0;
    char arr[MAX_LEN];

    RegisterCallback(Announce);

    do
    {
        strLen = enterArray(arr);
        printf("Entered account : %s\n", arr);
        Check_Account(arr, strLen);
        option();
    } while (isCorrect != 0 || input == 'y');

    return 0;
}

uint8_t enterArray(char *pArray)
{
    uint8_t strLen = 0;

    printf("Enter account %d: ", numOfAccount);

    fflush( stdin );
    scanf("%19[^\n]", pArray);
    clear_stdin();

    /* Get string lenght. */
    for (strLen = 0; (strLen < 20) && (*(pArray + strLen) != '\0'); strLen++)
    {
        ;
    }

    return strLen;

}

void Announce(status_enum_t status)
{
    isCorrect = status;

    switch (status)
    {
    case CORRECT:
        printf("Account is CORRECT!\n");
        break;

    case CHAR_INVALID:
        printf(" --- <!>: Account is CHAR_INVALID!\n");
        printf("\nPlease enter account with only alphanumeric\n");
        break;

    case LENGHT_INVALID:
        printf("--- <!>: Account is LENGHT_INVALID!\n");
        printf("\nPlease enter account with: maximum number of characters <= 10\n");
        break;
    }
}

void option()
{
    if(0 == isCorrect)
        {
            numOfAccount +=1;
            printf("\n------Enter 'y' to continue, enter any key to finish: ");
            printf("\n");
            scanf("%c", &input);
            if( 'y' != input)
            {
                printf("\n------Finish! Thank you very much!------\n");
            }
        }
}

void clear_stdin()
{
    int chr;
    while ((chr = getchar()) != '\n' && chr != '\n');
}
