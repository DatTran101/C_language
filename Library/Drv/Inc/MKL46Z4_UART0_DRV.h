/*
********************************************************************************
* @file     MKL46Z4_GPIO_DRV.h
* @author   DatTK2
* @version  V1
* @date     8, Feb 2023
*******************************************************************************/

#ifndef _MKL46Z4_UART0_DRV_H_
#define _MKL46Z4_UART0_DRV_H_

/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4_UART0_HAL.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

typedef void (*UART0_DRV_CallBack)(void);

typedef enum
{
  Even = 0U,
  Odd = 1U,
} Parity_type_e;

typedef enum
{
  LSB = 0,
  MSB = 1,
} MSB_First_type_e;



/*******************************************************************************
* Global variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief This Function used to initialize the UART0.
 *
 * @param
 */
void UART0_DRV_Init();

/**
 * @brief This Function used to set baudrate for UART0.
 *
 * @param: baudrate.
 */
void UART0_DRV_SetBaudrate(uint32_t baudrate);

/**
 * @brief This Function used to enable transmitter for UART0.
 *
 * @param: Interrupt mode or polling.
 */
void UART0_DRV_TransmitterEnable(Interrupt_polling_e mode);

/**
 * @brief This Function used to enable transmitter for UART0.
 *
 * @param
 */
void UART0_DRV_TransmitterDisable();

/**
 * @brief This Function used to enable receiver for UART0.
 *
 * @param: Interrupt mode or polling.
 */
void UART0_DRV_ReceiverEnable(Interrupt_polling_e mode);

/**
 * @brief This Function used to disable receiver for UART0.
 *
 * @param
 */
void UART0_DRV_ReceiverDisable();

/**
 * @brief This Function used to enable parity bit for UART0.
 *
 * @param: Even mode of Odd mode.
 */
void UART0_DRV_ParityEnable(Parity_type_e type);

/**
 * @brief This Function used to disable parity bit for UART0.
 *
 * @param
 */
void UART0_DRV_ParityDisable();

/**
 * @brief This Function used to configure numbers of bit transmit or receive.
 *
 * @param: Numbers of bit: 8 or 9 or 10.
 */
void UART0_DRV_ConfigData(uint8_t Num_bit);

/**
 * @brief This Function used to select numbers of stop bit for UART0.
 *
 * @param: Numbers of bit: 1 or 2.
 */
void UART0_DRV_StopBit(uint8_t Num_bit);

/**
 * @brief This Function used to select LSB type or MSB type for UART0.
 *
 * @param: Numbers of bit: LSB mode or MSB mode.
 */
void UART0_DRV_ConfigMSBF(MSB_First_type_e type);

/**
 * @brief This Function used to transmit character from MCU.
 *
 * @param 1: Data what need to send.
 * @param 2: Interrupt mode or polling.
 */
void UART0_DRV_TransmitChar(char chr, Interrupt_polling_e mode );

/**
 * @brief This Function used to receive data from MCU.
 *
 * @param 1: Interrupt mode or polling.
 */
char UART0_DRV_ReceiveData(Interrupt_polling_e mode);

/**
 * @brief This Function used to get the address of the function.
 *
 * @param Address of the function to be called.
 */
void UART0_DRV_RegisterCallback(UART0_DRV_CallBack func_name);

/**
 * @brief This Function used to deinitialize the UART0.
 *
 * @param
 */
void UART0_DRV_Deinit();

#endif