/*
********************************************************************************
* @file     Srec.h
* @author   DatTK2
* @version  V1
* @date     11, Feb 2023
*******************************************************************************/


#ifndef _SREC_H_
#define _SREC_H_


/*******************************************************************************
 * Includes
*******************************************************************************/

#include <stdint.h>


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define MAX_NUMBERS_BYTE_OF_DATA_FIELD      253U


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief This macro used used for information
 *        that has been converted to hexadecimal.
 */
typedef struct
{
    uint8_t byte_count;
    uint16_t address;
    uint8_t data[MAX_NUMBERS_BYTE_OF_DATA_FIELD];
    uint8_t check_sum;

} get_line_data_t;

typedef struct
{
    char record_start;
    char record_type;
    uint16_t length;

} record_structure_t;
/*******************************************************************************
 * API
*******************************************************************************/

/**
 * @brief This Function used to parser lines of srec file.
 *
 * @param 1: The pointer point to the array, that is storing information of line.
 * @param 2: The pointer point to the variable, that used to recive converted data.
 * @param 2: The pointer point to the variable, that used to recive information of end of line.
 */
uint8_t srec_parser(const char *buffer, get_line_data_t *get_data, uint8_t *end_of_file);

/**
 * @brief This Function used to convert 2 character to 1 byte hexa type.
 *
 * @param 1: The array has 2 character
 */
uint8_t convert_chars_to_hex_8bit(const char hex[2]);

/**
 * @brief This Function used to convert 4 character to 2 byte hexa type.
 *
 * @param 1: The array has 4 character
 */
uint16_t convert_chars_to_hex_16bit(const char hex[4]);

#endif /*_SREC_H_*/

/**End of file**/