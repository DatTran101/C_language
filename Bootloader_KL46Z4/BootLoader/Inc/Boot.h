/*
********************************************************************************
* @file     MKL46Z4_UART_HAL.h
* @author   DatTK2
* @version  V1
* @date     18, Feb 2023
*******************************************************************************/


#ifndef __BOOT_H__
#define __BOOT_H__


/*******************************************************************************
  Includes
*******************************************************************************/

#include <stdint.h>


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define APP_MSP_ADDRESS     0xA000U     /* Start main stack pointer for application. */

#define APP_START_ADDRESS   0xA004U     /* Start application address. */


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

typedef void (*pFunc)(void);


/**
 * @brief This Function used to run user application.
 *
 * @param
 */
void BOOT_User_App(void);

/**
 * @brief This Function used to eraser number sectors of flash, begin from application code
 *
 * @param uint8_t: numbers of sectors
 *
 */
void BOOT_Eraser_Flash(uint8_t num_sector);


void BOOTLOADER_DRV_Eraser_Flash(uint8_t num_sector);
/**
 * @brief This Function used to write data to flash.
 *
 * @param 1: address field of user application.
 * @param 2: data field of user application.
 * @param 3: data length.
 */
void BOOT_Write_App_To_Flash(uint32_t address, uint8_t *data, uint8_t data_length);

#endif /*__BOOT_H__*/

/**End of file**/