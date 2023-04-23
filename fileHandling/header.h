
/*
*******************************************************************************
* @file    header.h
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions prototypes
*******************************************************************************/


#ifndef __HEADER_H__
#define __HEADER_H__

/********************************************************************************************
 * Include
 *******************************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define START_CODE_INDEX 0
#define BYTE_COUNT_INDEX 1
#define ADDRESS_INDEX 3
#define RECORD_TYPE_INDEX 7
#define DATA_INDEX 9
#define LENGTH_0_CONTAIN_DATA 11

/*
 * Declare struct type. */
typedef struct
{
    uint8_t byteCount;
    uint16_t address;
    uint8_t recordType;
    uint8_t data[0xff];
    uint8_t checkSum;
} t_hexRecord;

/*
 * Declare enum type. */
typedef enum
{
    HEX_OK,
    HEX_MISSING_START_CODE,
    HEX_INVALID_CHARACTER,
    HEX_INVALID_LENGTH,
    HEX_ERROR_CHECKSUM,
    HEX_EOF,
} HEX_STATUS;

typedef enum
{
    STATUS_OK,
    STATUS_ERROR,
} STATUS;


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief Use to show menu
 *
 * @return void
 */

/**
 * @brief Use to check if the characters entered in the menu are valid
 *
 * @param request
 * @return STATUS
 */
STATUS checkCharacter(char *request);

void menu();

/**
 * @brief Open hex file
 * @param fileName: Hex file name
 * @param mode: File access mode
 * @return FILE
 */
FILE *openFile(const char *fileName, const char *mode);

/**
 * @brief Print out errors of hex file
 *
 * @return void
 */
void checkHexFile();

/**
 * @brief Use to make menu selections
 *
 * @return void
 */
STATUS actions();

/**
 * @brief Convert hex to decimal
 * @param currentChar: The character you want to convert
 * @return uint8_t decimal digit.
 */
uint8_t hex2U8(char *currentChar);

/**
 * @brief Convert hex to decimal
 * @param currentChar: The character you want to convert
 * @return uint16_t decimal digit.
 */
uint16_t hex2U16(char *currentChar);

/**
 * @brief Convert hex to decimal
 * @param record: Record struct of hex file
 * @return uint8_t Checksum.
 */
uint8_t checkSum(t_hexRecord *record);

/**
 * @brief Get character length per line
 * @param dataLine: String of characters on 1 line
 * @return uint16_t Character length.
 */
uint16_t getLength(char *dataLine);

/**
 * @brief Check character validity
 * @param dataLine: String of characters on 1 line
 * @param lengthLine: Character length per line
 * @return STATUS : STATUS_OK (Valid) or STATUS_ERROR (Invalid)
 */
STATUS isValidChar(char *dataLine, uint16_t lengthLine);

/**
 * @brief Check which record type belongs to
 * @param record: Record struct of hex file
 * @return void : Print out the corresponding record type
 */
void recordType(uint8_t record);

/**
 * @brief Check for possible errors of hex files
 * @param dataLine: String of characters on 1 line
 * @param record: Record struct of hex file
 * @return HEX_STATUS : Returns error statuses of hex files
 */
HEX_STATUS readHexFile(char *dataLine, t_hexRecord *record);
#endif
/****************************************************************************
 * EOF
 ***************************************************************************/
