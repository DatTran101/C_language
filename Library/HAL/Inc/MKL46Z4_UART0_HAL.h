/*
********************************************************************************
* @file     MKL46Z4_UART_HAL.h
* @author   DatTK2
* @version  V1
* @date     7, Feb 2023
*******************************************************************************/

#ifndef _MKL46Z4_UART0_HAL_H_
#define _MKL46Z4_UART0_HAL_H_


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

typedef enum
{

  Polling = 0,
  Interrupt = 1,

} Interrupt_polling_e;


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
 * @brief This Function used to set baudrate for UART0.
 *
 * @param: baudrate.
 */
void UART0_HAL_SetBaudrate(uint32_t baudrate);

/**
 * @brief This Function used to configure number of bit transmit or Receive
 *
 * @param: Number of bit.
 */
void UART0_HAL_ConfigData(uint8_t Num_bit);

/**
 * @brief This Function used to transmit character.
 *
 * @param: Data have char styte.
 */
void UART0_HAL_TransmitChar(char data, Interrupt_polling_e mode);

/**
 * @brief This Function used to transmit string.
 *
 * @param: Pointer to character array.
 */
void UART_HAL_TransmitString(const char *str, Interrupt_polling_e mode);

/**
 * @brief This Function used to receive data.
 *
 * @param: Mode interrupt or polling.
 */
char UART0_HAL_ReceiveData(Interrupt_polling_e mode);

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

/**
 * @brief This Function used to enable parity bit.
 *
 * @param
 */
static inline void UART0_HAL_ParityEnable(void)
{
  /* Set PE bit in C1 register to 1.*/
  UART0->C1 |= UART0_C1_PE_MASK;
}

/**
 * @brief This Function used to disable parity bit.
 *
 * @param
 */
static inline void UART0_HAL_ParityDisable(void)
{
  /* Clear PE bit in C1 register to 0.*/
  UART0->C1 &= ~UART0_C1_PE_MASK;
}

/**
 * @brief This Function used to select even mode for parity mode.
 *
 * @param
 */
static inline void UART0_HAL_ParityEven(void)
{
  /* Clear PT bit in C1 register to 0.*/
  UART0->C1 &= ~UART0_C1_PT_MASK;
}

/**
 * @brief This Function used to select odd mode for parity mode.
 *
 * @param
 */
static inline void UART0_HAL_ParityOdd(void)
{
  /* Set PT bit in C1 register to 1.*/
  UART0->C1 |= UART0_C1_PT_MASK;
}

/**
 * @brief This Function used to enable transmitter for UART0.
 *
 * @param
 */
static inline void UART0_HAL_TransmitterEnable(void)
{
  /* Set TE bit in C2 register to 1.*/
  UART0->C2 |= UART0_C2_TE_MASK;
}

/**
 * @brief This Function used to disable transmitter for UART0.
 *
 * @param
 */
static inline void UART0_HAL_TransmitterDisable(void)
{
  /* Clear TE bit in C2 register to 0.*/
  UART0->C2 &= ~UART0_C2_TE_MASK;
}

/**
 * @brief This Function used to select interrupt mode for UART0 with UART0 is transmitter.
 *
 * @param
 */
static inline void UART0_HAL_TransmitterInterrupt(void)
{
  /* Set TIE bit in C2 register to 1.*/
  UART0->C2 |= UART0_C2_TIE_MASK;
}

/**
 * @brief This Function used to select polling mode for UART0 with UART0 is transmitter.
 *
 * @param
 */
static inline void UART0_HAL_TransmitterPolling(void)
{
  /* Clear TIE bit in C2 register to 0.*/
  UART0->C2 &= ~UART0_C2_TIE_MASK;
}

/**
 * @brief This Function used to enable Receiver for UART0.
 *
 * @param
 */
static inline void UART0_HAL_ReceiverEnable(void)
{
  /* Set RE bit in C2 register to 1.*/
  UART0->C2 |= UART0_C2_RE_MASK;
}

/**
 * @brief This Function used to disable Receiver for UART0.
 *
 * @param
 */
static inline void UART0_HAL_ReceiverDisable(void)
{
  /* Clear RE bit in C2 register to 0.*/
  UART0->C2 &= ~UART0_C2_RE_MASK;
}

/**
 * @brief This Function used to select interrupt mode for UART0 with UART0 is Receiver.
 *
 * @param
 */
static inline void UART0_HAL_ReceiverInterrupt(void)
{
  /* Set RIE bit in C2 register to 1.*/
  UART0->C2 |= UART_C2_RIE_MASK;
}

/**
 * @brief This Function used to select polling mode for UART0 with UART0 is Receiver.
 *
 * @param
 */
static inline void UART0_HAL_ReceiverPolling(void)
{
  /* Clear RIE bit in C2 register to 0.*/
  UART0->C2 &= ~UART0_C2_RIE_MASK;
}

/**
 * @brief This Function used to select stop bit is 1.
 *
 * @param
 */
static inline void UART0_HAL_StopBit_1(void)
{
  /* Clear SBNA bit in BDH register to 0.*/
  UART0->BDH &= ~UART0_BDH_SBNS_MASK;
}

/**
 * @brief This Function used to select stop bit is 2.
 *
 * @param
 */
static inline void UART0_HAL_StopBit_2(void)
{
  /* SET SBNA bit in BDH register to 1.*/
  UART0->BDH |= UART0_BDH_SBNS_MASK;
}

/**
 * @brief This Function used to select LSB.
 *
 * @param
 */
static inline void UART0_HAL_LSB(void)
{
  /* Clear MSBF bit in S2 register to 1.*/
  UART0->S2 &= ~UART0_S2_MSBF_MASK;
}

/**
 * @brief This Function used to select MSB.
 *
 * @param
 */
static inline void UART0_HAL_MSB(void)
{
  /* Set MSBF bit in S2 register to 1.*/
  UART0->S2 |= UART0_S2_MSBF_MASK;
}


#endif /*_MKL46Z4_UART0_HAL_H_*/