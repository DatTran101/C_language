/*
********************************************************************************
* @file     MKL46Z4_UART0_DRV.c
* @author   DatTK2
* @version  V1
* @date     8, Feb 2023
*******************************************************************************/


/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4_UART0_DRV.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Globla variables
******************************************************************************/

UART0_DRV_CallBack    DRV_CallbackFunction = NULL;


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief This Function used to handl cacllback function.
 *
 * @param
 */
static void UART0_DRV_CallbackHandler();


void UART0_DRV_Init()
{
  UART0_HAL_Init();

  UART0_HAL_RegisterCallBack(UART0_DRV_CallbackHandler);
}

void UART0_DRV_SetBaudrate(uint32_t baudrate)
{
  UART0_HAL_SetBaudrate(baudrate);
}

void UART0_DRV_TransmitterEnable(Interrupt_polling_e mode)
{
  /* Enable transmitter for UART0 */
  UART0_HAL_TransmitterEnable();

  if(mode == Polling)
  {
    /* Select polling mode for Transmitter mode. */
    UART0_HAL_TransmitterPolling();
  }
  else if(mode == Interrupt)
  {
    /* Select interrupt mode for Transmitter mode. */
    UART0_HAL_TransmitterInterrupt();
  }

}

void UART0_DRV_TransmitterDisable()
{
  UART0_HAL_TransmitterDisable();
}

void UART0_DRV_ReceiverEnable(Interrupt_polling_e mode)
{
  /* Enable transmitter for UART0 */
  UART0_HAL_ReceiverEnable();

  if(mode == Polling)
  {
    /* Select polling mode for receiver mode. */
    UART0_HAL_ReceiverPolling();
  }
  else if(mode == Interrupt)
  {
    /* Select interrupt mode for receiver mode. */
    UART0_HAL_ReceiverInterrupt();
  }

}

void UART0_DRV_ReceiverDisable()
{
  UART0_HAL_ReceiverDisable();
}

void UART0_DRV_ParityEnable(Parity_type_e type)
{
  /* Enable parity bit. */
  UART0_HAL_ParityEnable();

  if(type == Even)
  {
    /* Select Even mode. */
    UART0_HAL_ParityEven();
  }
  else if(type == Odd)
  {
    /* Select Odd mode. */
    UART0_HAL_ParityOdd();
  }

}

void UART0_DRV_ParityDisable()
{
  UART0_HAL_ParityDisable();
}

void UART0_DRV_ConfigData(uint8_t Num_bit)
{
  UART0_HAL_ConfigData(Num_bit);
}

void UART0_DRV_StopBit(uint8_t Num_bit)
{
  if(1 == Num_bit)
  {
    /* Select 1 stop bit. */
    UART0_HAL_StopBit_1();
  }
  else if(2 == Num_bit)
  {
    /* Select 1 stop bit. */
    UART0_HAL_StopBit_2();
  }
}

void UART0_DRV_ConfigMSBF(MSB_First_type_e type)
{
  if(0 == type)
  {
    /* Select LSB mode. */
    UART0_HAL_LSB();
  }
  else if(1 == type)
  {
    /* Select MSB mode. */
    UART0_HAL_MSB();
  }
}

void UART0_DRV_TransmitChar(char chr, Interrupt_polling_e mode)
{
  UART0_HAL_TransmitChar(chr, mode);
}

char UART0_DRV_ReceiveData(Interrupt_polling_e mode)
{
  return UART0_HAL_ReceiveData(mode);
}

void UART0_DRV_RegisterCallback(UART0_DRV_CallBack func_name)
{
  DRV_CallbackFunction = func_name;
}

static void UART0_DRV_CallbackHandler(void)
{
    if (NULL != DRV_CallbackFunction)
    {
        DRV_CallbackFunction();
    }
}

void UART0_DRV_Deinit()
{
  UART0_HAL_Deinit();
}


