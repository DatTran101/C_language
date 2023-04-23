/*
********************************************************************************
* @file     MKL46Z4_UART.h
* @author   DatTK2
* @version  V1
* @date     7, Feb 2023
*******************************************************************************/

#ifndef _MKL46Z4_UART0_H_
#define _MKL46Z4_UART0_HAL_H__H_


/*******************************************************************************
  Includes
*******************************************************************************/

#include <stdlib.h>
#include "MKL46Z4.h"


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

/**
 * @brief This macro used to reate a callback function.
 *
 * @param
 */
typedef void (*UART0_HAL_Callback)(void);

/**
 * @brief This macro used to locate ports in SCGC5.
 *
 */
typedef enum
{
  PORT_A = SIM_SCGC5_PORTA_SHIFT,
  PORT_B = SIM_SCGC5_PORTB_SHIFT,
  PORT_C = SIM_SCGC5_PORTC_SHIFT,
  PORT_D = SIM_SCGC5_PORTD_SHIFT,
  PORT_E = SIM_SCGC5_PORTE_SHIFT,

} SCGC5_mode_t;

/*******************************************************************************
  Function Prototype
*******************************************************************************/

/**
 * @brief This Function used to initialize the UART0.
 *
 * @param
 */
void UART0_HAL_Init(void);

/**
 * @brief This Function used to set clock for port.
 * @param : port location in SCGC5 register.
 */
void UART0_SetClock_Port(SCGC5_mode_t SCGC5_feild);

/**
 * @brief This Function used to configure port used for UART0.
 *
 * @param 1: The pointer has PORT_Type type.
 * @param 2: The position of the pin needs set.
 * @param 2: The MUX field of pin.
 */
void UART0_Config_Pin_MUX(PORT_Type *PORTx, uint8_t PINx, uint8_t status);

/**
 * @brief This Function used to configure switch used for UART0.
 *
 * @param 1: The pointer has GPIO_Type type.
 * @param 2: The pointer has PORT_Type type.
 * @param 2: The position of the pin needs set.
 */
void UART0_Config_SW(GPIO_Type *GPIOx, PORT_Type *PORTx, uint8_t PINx);

/**
 * @brief This Function used to read state of pins.
 *
 * @param 1: The pointer has GPIO_Type type.
 * @param 2: The position of the pin needs read.
 */
uint8_t Read_Pin(GPIO_Type *GPIOx, uint8_t PINx);

/**
 * @brief This Function used to transmit character.
 *
 * @param: Data have char styte.
 */
void UART0_HAL_TransmitChar(char data);

/**
 * @brief This Function used to transmit string.
 *
 * @param: Pointer to character array.
 */
void UART0_HAL_TransmitString(const char *str);

/**
 * @brief This Function used to receive data.
 *
 * @return: The chracter is recived.
 */
char UART0_HAL_ReceiveData();

/**
 * @brief This Function used to get the address of the function.
 *
 * @param Address of the function to be called.
 */
void UART0_HAL_RegisterCallBack(UART0_HAL_Callback func_name);

/**
 * @brief This Function used to deinitialize the UART0.
 *
 * @param
 */
void UART0_HAL_Deinit();

#endif /*_MKL46Z4_UART0_HAL_H_*/

/**End of file**/