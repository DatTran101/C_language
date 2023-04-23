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
#include "MKL46Z4_UART0.h"

/****************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define MCGFLLCLK_CLOCK 1U
#define OSR             15U
#define USE_8_BIT_DATA  8U
#define USE_9_BIT_DATA  8U
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

  /* sbr_val variable use to store Baud Rate Modulo Divisor. */
  uint16_t sbr_val = 0;

  /* Enable clock for UART0.*/
  SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;

  /* UART0 Clock Source Select: MCGFLLCLK clock or MCGPLLCLK/2 clock. */
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK_CLOCK);

  /* Caculate Baud Rate Modulo Divisor. */
  sbr_val = (24000000 / (115200 * (OSR + 1)));

  /* Write low 8 bit of Baud Rate Modulo Divisor into BDL register. */
  UART0->BDL = (sbr_val & UART_BDL_SBR_MASK);

  /* Write high 5 bit of Baud Rate Modulo Divisor into BDH register. */
  UART0->BDH |= ((sbr_val >> 8U) & UART_BDH_SBR_MASK);

  /* Clear bit M10 of C4 register to use 8 bit mode or 9 bit mode. */
  UART0->C4 &= ~UART0_C4_M10_MASK;
  /* Clear bit M of C1 register to use 8 bit mode. */
  UART0->C1 &= ~UART0_C1_M_MASK;

  /* Clear PE bit in C1 register to 0 to disable parity bit.*/
  UART0->C1 &= ~UART0_C1_PE_MASK;

  /* Clear SBNA bit in BDH register to 0 to used 1 stop bit mode.*/
  UART0->BDH &= ~UART0_BDH_SBNS_MASK;

  /* Set MSBF bit in S2 register to 1 to used LSB mode.*/
  UART0->S2 &= ~UART0_S2_MSBF_MASK;

  /* Set RE bit in C2 register to 1 to enable Receiver.*/
  UART0->C2 |= UART0_C2_RE_MASK;
  /* Set RIE bit in C2 register to 1 to used receiver interrupt mode.*/
  UART0->C2 |= UART_C2_RIE_MASK;

  /* Set TE bit in C2 register to 1 to transmitter enable.*/
  UART0->C2 |= UART0_C2_TE_MASK;
}

void UART0_SetClock_Port(SCGC5_mode_t SCGC5_feild)
{
  SIM->SCGC5 |= ((uint32_t)1U << SCGC5_feild);
}

void UART0_Config_Pin_MUX(PORT_Type *PORTx, uint8_t PINx, uint8_t status)
{

  /* Set MUX field is equal to "status value"  */
  PORTx->PCR[PINx] |= PORT_PCR_MUX(status);
}

void UART0_Config_SW(GPIO_Type *GPIOx, PORT_Type *PORTx, uint8_t PINx)
{

  /* Set MUX field is equal to "status value"  */
  PORTx->PCR[PINx] |= PORT_PCR_MUX(1U);

  /* Clear pin to config input */
  GPIOx->PDDR &= ~((uint32_t)1U << PINx);

  /* Set bit of pull enable field to enable "pull enable field" */
  PORTx->PCR[PINx] |= PORT_PCR_PE(1U);

  /* Set bit of pull section field to pullup internal resistor*/
  PORTx->PCR[PINx] |= PORT_PCR_PS(1U);
}

uint8_t Read_Pin(GPIO_Type *GPIOx, uint8_t PINx)
{
  /* Read  value of corresponding pin*/
  return (uint8_t)((GPIOx->PDIR >> PINx) & 1U);
}

void UART0_HAL_TransmitChar(char data)
{

  while (!(UART0->S1 & UART_S1_TDRE_MASK))
  {
  }
  /* Write data to the Tx buffer. */
  UART0->D = data;
}

void UART0_HAL_TransmitString(const char *str)
{
  /* while str pointer different null, write data into string. */
  while (*str)
  {
    /* Write data into string. */
    UART0_HAL_TransmitChar(*str++);
  }
}

char UART0_HAL_ReceiveData(void)
{
  return UART0->D;
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

/**End of file**/
