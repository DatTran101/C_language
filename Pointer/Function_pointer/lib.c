

#include "header.h"
#include <stdbool.h>
#include <stdio.h>


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/

func pF = NULL;


/*******************************************************************************
* Add static API prototype in C file inside :
* Prototypes
******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

void RegisterCallback(func func_add)
{
    pF = func_add;
}

void Check_Account(char *ptr, uint8_t lenght)
{
    uint16_t chr = 0;
    uint8_t index = 0;
    bool isValid = true;

    if (lenght > 10)
    {
        pF(LENGHT_INVALID);
        isValid = false;
    }
    else if (0 != lenght)
    {
        for (index = 0; index < lenght; index++)
        {
            chr = *(ptr + index);

            bool isAlphabet = ('a' <= chr && chr <= 'z') ||
                              ('A' <= chr && chr <= 'Z');

            bool isNumber = ('0' <= chr && chr <= '9');

            if (!isNumber && !isAlphabet)
            {
                pF(CHAR_INVALID);
                isValid = false;
                break;
            }
        }
    }
    else
    {
        pF(CHAR_INVALID);
        isValid = false;
    }

    if (isValid)
    {
        pF(CORRECT);
    }

}