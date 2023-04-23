
/*
*******************************************************************************
* @file    menu.c
* @author  Tran_Khanh_Dat
* @brief   This file is used to handle user selections
*******************************************************************************/


/*****************************************************************
 * Include
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "header.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

void menu()
{
    system("cls");
    printf("********************************************CHECK HEX FILE*********************************************\n");
    printf("|1. Enter 'c' to enter the hex file you want to check                                                 |\n");
    printf("|2. Enter 'e' to exit program                                                                         |\n");
    printf("*******************************************************************************************************\n");
    printf("Please enter your request: ");
    fflush(stdin);
}
FILE *openFile(const char *fileName, const char *mode)
{
    FILE *fileOpen = fopen(fileName, mode);
    if (fileOpen == NULL)
    {
        perror(fileName);

    }
    else
    {
        /* MISRA standard. */
    }
    return fileOpen;
}
void checkHexFile()
{
    FILE *hexFile;
    char dataLine[522];
    t_hexRecord record;
    uint8_t line = 1U;
    HEX_STATUS status;
    char fileName[100];
    printf("Enter hex file path to parse intel hex (Example: hex.txt): ");
    scanf("%s", fileName);
    hexFile = openFile(fileName, "rb");
    printf("Start read Hex File\n\n");
    while ((fgets(dataLine, sizeof(dataLine), hexFile) != NULL) && ((status = readHexFile(dataLine, &record)) != HEX_EOF))
    {
        printf("<>Line number: %hhu", line);
        line++;
        switch (status)
        {
        case HEX_MISSING_START_CODE:
            printf("\n\tNOTE: Syntax error\n");
            printf("\t<!> There is no start code in this line\n\n");
            break;

        case HEX_INVALID_CHARACTER:
            printf("\n\tNOTE: Syntax error\n");
            printf("\t<!> Characters not in the format of the Hex file\n\n");
            break;

        case HEX_INVALID_LENGTH:
            printf("\n\tNOTE: Not enough the number of bytes compared to the count byte\n\n");
            break;
        case HEX_ERROR_CHECKSUM:
            printf("\n\tNOTE: Check sum Fault\n\n");
            break;

        default:
            if (record.recordType > 5U)
            {
                printf("\n\tNOTE: Record type Fault\n\n");
            }
            else
            {
                printf(" %s", dataLine);
                printf("\t[ADDRESS]          : 0x0000");
                for (uint8_t index = ADDRESS_INDEX; index < ADDRESS_INDEX + 4; index++)
                {
                    printf("%c", dataLine[index]);
                }
                recordType(record.recordType);
                printf("\t[DATA BYTE]        : %hhu bytes\n", record.byteCount);
                printf("\t[DATA]             : ");
                for (uint8_t index = DATA_INDEX; index < DATA_INDEX + record.byteCount * 2; index++)
                {
                    printf("%c", dataLine[index]);
                }
                printf("\n\n");
            }
            break;
        }
    }

    fclose(hexFile);
}

STATUS actions()
{
    STATUS retVal = STATUS_OK;
    char request;
    while (checkCharacter(&request) != STATUS_OK)
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
    case 'c':
        checkHexFile();
        system("pause");
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
