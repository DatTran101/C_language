
/*
*******************************************************************************
* @file    header.h
* @author  Tran_Khanh_Dat
* @brief   Write a program that allows the user to enter an account from the keyboard.
*          Use char array arr[20] to store accounts.
*
*           Check for error accounts:
*
*           If the account is >10 characters (LENGHT_INVALID)
*           If you enter an account with characters other than alphanumeric (CHAR_INVALID).
*******************************************************************************/


#ifndef __header_h__
#define __header_h__
#include <stdint.h>


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

typedef enum _statetype
{
    CORRECT,
    CHAR_INVALID,
    LENGHT_INVALID
} status_enum_t;


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

typedef void (*func)(status_enum_t status);

void RegisterCallback(func func_add);

void Check_Account(char *ptr, uint8_t lenght);

void Announce(status_enum_t status);

#endif