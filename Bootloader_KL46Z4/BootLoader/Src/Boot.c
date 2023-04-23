/*
********************************************************************************
* @file     MKL46Z4_UART0_HAL.c
* @author   DatTKD
* @version  V1
* @date     18, Feb 2023
*******************************************************************************/


/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4.h"
#include "MKL46Z4_Flash.h"
#include "MKL46Z4_UART0.h"
#include "Boot.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define     CURRENT_MAX_LEN     16U
#define     RESET_VALUE         0xffU


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

void BOOT_User_App(void)
{
    /* Disable interrupt before configure vector table. */
    __disable_irq();

    /* Set vector table to new address. */
    SCB->VTOR = APP_MSP_ADDRESS;

   /* Set address of main stack pointer. */
    __set_MSP(*(volatile uint32_t *)APP_MSP_ADDRESS);

    /* Set application function address. */
    pFunc App_Func = *((pFunc *)APP_START_ADDRESS);

    /* Run current application. */
    App_Func();
}

void BOOT_Eraser_Flash(uint8_t num_sector)
{
    Erase_Multi_Sector(APP_MSP_ADDRESS, num_sector);
}

void BOOT_Write_App_To_Flash(uint32_t address, uint8_t *data, uint8_t data_length)
{
    uint8_t i = 0;

    for (i = 0; i < data_length; i += 4)
    {

        NVIC_DisableIRQ(UART0_IRQn);

        Program_LongWord_8B(address + i, &data[i]);

        NVIC_EnableIRQ(UART0_IRQn);
    }

    /* Reset data. */
    for(i = 0; i < CURRENT_MAX_LEN; i++)
    {
        data[i] = RESET_VALUE;
    }
}

/**End of file**/