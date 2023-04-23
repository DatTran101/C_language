/*
********************************************************************************
* @file     MKL46Z4_UART0_HAL.c
* @author   DatTKD
* @version  V1
* @date     7, Feb 2023
*******************************************************************************/

/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4.h"
#include "MKL46Z4_UART0_HAL.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define MCGFLLCLK_CLOCK 1U
#define OSR 15U
#define USE_8_BIT_DATA 8U
#define USE_9_BIT_DATA 8U
#define USE_10_BIT_DATA 8U


/*******************************************************************************
* Variables
******************************************************************************/

UART0_HAL_Callback HAL_CallbackFunction;


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

void UART0_HAL_Init()
{
  /* Enable clock for UART0.*/
  SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;

  /* UART0 Clock Source Select: MCGFLLCLK clock or MCGPLLCLK/2 clock. */
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK_CLOCK);
}

void UART0_HAL_SetBaudrate(uint32_t baudrate)
{
  /* sbr_val variable use to store Baud Rate Modulo Divisor. */
  uint16_t sbr_val = 0;

  SystemCoreClockUpdate();

  /* Caculate Baud Rate Modulo Divisor. */
  sbr_val = (SystemCoreClock / (baudrate * (OSR + 1)));

  /* Write low 8 bit of Baud Rate Modulo Divisor into BDL register */
  UART0->BDL = (sbr_val & UART_BDL_SBR_MASK);
  /* Write high 5 bit of Baud Rate Modulo Divisor into BDH register */
  UART0->BDH |= ((sbr_val >> 8U) & UART_BDH_SBR_MASK);
}

void UART0_HAL_ConfigData(uint8_t Num_bit)
{

  if (USE_8_BIT_DATA == Num_bit)
  {
    /* Clear bit M10 of C4 register to use 8 bit mode or 9 bit mode. */
    UART0->C4 &= ~UART0_C4_M10_MASK;
    /* Clear bit M of C1 register to use 8 bit mode. */
    UART0->C1 &= ~UART0_C1_M_MASK;
  }
  else if (USE_9_BIT_DATA == Num_bit)
  {
    /* Clear bit M10 of C4 register to select use 8 bit mode or 9 bit mode. */
    UART0->C4 &= ~UART0_C4_M10_MASK;
    /* set bit M of C1 register to use 9 bit mode. */
    UART0->C1 |= UART0_C1_M_MASK;
  }
  else if (USE_10_BIT_DATA == Num_bit)
  {
    /* set bit M10 of C4 register to use 10 bit mode. */
    UART0->C4 |= UART0_C4_M10_MASK;
  }
}

void UART0_HAL_TransmitChar(char data, Interrupt_polling_e mode)
{
  if(mode == Polling)
  {
    /* Wait for Tx buffer to be empty. */
    while (!(UART0->S1 & UART_S1_TDRE_MASK))
    {}
    /* Write data to the Tx buffer. */
    UART0->D = data;
  }
  else if(mode == Interrupt)
  {
    UART0->D = data;
  }

}

void UART_HAL_TransmitString(const char *str, Interrupt_polling_e mode)
{
  /* while str pointer different null, write data into string. */
  while (*str)
  {
    /* Write data into string. */
    UART0_HAL_TransmitChar(*str++, mode);
  }
}

char UART0_HAL_ReceiveData(Interrupt_polling_e mode)
{
  char temp;
  if (mode == Polling)
  {
    /* Wait for Rx buffer to be full. */
    while (!(UART0->S1 & UART_S1_RDRF_MASK))
    {}
    /* Read data from the Rx buffer. */
    temp = UART0->D;
  }
  else if (mode == Interrupt)
  {
    /* Read data from the Rx buffer. */
    temp = UART0->D;
  }
  return temp;
}

void UART0_HAL_RegisterCallBack(UART0_HAL_Callback func_name)
{
  HAL_CallbackFunction = func_name;
}

void UART0_IRQHandler(void)
{
  if (NULL != HAL_CallbackFunction)
    {
    HAL_CallbackFunction();
    }
}

void UART0_HAL_Deinit()
{
  SIM->SCGC4 &= ~SIM_SCGC4_UART0_MASK;
  SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
}
