/*
********************************************************************************
* @file     MKL46Z4_LCD16x2_DRV.h
* @author   DatTK2
* @version  V1
* @date     4, Jan 2023
*******************************************************************************/


#ifndef _MKL46Z4_LCD16x2_DRV_H_
#define _MKL46Z4_LCD16x2_DRV_H_ /**< Symbol preventing repeated inclusion */


/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4_LCD16x2_UserMacro.h"
#include "string.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define CLEAR_DISPLAY_SCREEN                    0x01U
#define RETURN_HOME                             0x02U
#define SHIFT_CURSOR_TO_LEFT                    0x04U
#define SHIFT_CURSOR_TO_RIGHT                   0x06U
#define DISTLAY_ON_CURSOR_OFF                   0x0CU
#define LCD_INIT                                0x30U
#define TWO_LINE_AND_5X7_MATRIX                 0x38U
#define ACTIVATE_SECOND_LINE                    0x3CU
#define CURSOR_TO_BEGINNING_OF_FIRST_LINE       0x80U
#define CURSOR_TO_BEGINNING_OF_SECOND_LINE      0xC0U


/*******************************************************************************
* Global variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief This Function used to init LCD.
 * @param
 *
 */
void LCD16x2_DRV_Init();

/**
 * @brief This Function used to send Command into Instructor Register of LCD.
 * @param
 * Param: Command code.
 */
void LCD16x2_SendCommand(unsigned char cmd);

/**
 * @brief This Function used to clear lCD screen.
 * @param
 *
 */
void LCD16x2_DRV_Clear();

/**
 * @brief This Function used to bring the cursor position to the desired position.
 * @param
 * Param1: x describes the row where the cursor is being set ( 0 <= x <= 1).
 * Param2: y describes the column where the cursor is being set ( 0 <= y <= 15).
 */
void LCD16x2_DRV_GotoXY(uint8_t x, uint8_t y);

/**
 * @brief This Function used to write a character on the lcd.
 * @param
 * Param: A character will be displayed on the LCD screen.
 */
void LCD16x2_DRV_WriteChar(unsigned char chr);

/**
 * @brief This Function used to write a string on the lcd.
 * @param
 * Param: A string will be displayed on the LCD screen.
 */
void LCD16x2_DRV_WriteString(char *string);

/**
 * @brief This Function used to generate delay with unit ms.
 * @param
 * Param: Time delay in milliseconds.
 */
void delay_ms(uint32_t n);

#endif /*_MKL46Z4_LCD16x2_DRV_H_*/