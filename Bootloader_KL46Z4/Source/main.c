/*
********************************************************************************
* @file     Srec.c
* @author   DatTK2
* @version  V1
* @date     11, Feb 2023
*******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "Queue.h"
#include "Srec.h"
#include "Boot.h"
#include "MKL46Z4_Flash.h"
#include "MKL46Z4_UART0.h"
#include "MKL46Z4.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

/* Define pin name for green led and red led */
#define SW1_PORTC3 3U
#define ALTERNATE2 2U

/* Define pin name for UART0 TX. */
#define UART0_RX 1U
#define UART0_TX 2U


/*******************************************************************************
* Variables
******************************************************************************/

static uint8_t i = 0U;
static char re_data;
static char *ptr = NULL;

/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

void Get_Data(void);
/**
 * @brief This Function used to write data of srec file to flash
 *
 */
void write_app_to_flash(void);

/******************************************************************************
 *Code
 ******************************************************************************/

int main(void)
{

  uint16_t n = 200000U;

  UART0_HAL_Init();

  /* Configure Pin 3 of PORTC is start in signal from button. */
  UART0_SetClock_Port(PORT_C);
  UART0_Config_SW(GPIOC, PORTC, SW1_PORTC3);

  /* Configure Pin 1 and 2 of PORTA to perform the UART0. */
  UART0_SetClock_Port(PORT_A);
  UART0_Config_Pin_MUX(PORTA, UART0_RX, ALTERNATE2);
  UART0_Config_Pin_MUX(PORTA, UART0_TX, ALTERNATE2);

  UART0_HAL_RegisterCallBack(Get_Data);

  NVIC_SetPriority(UART0_IRQn, 1);

  NVIC_ClearPendingIRQ(UART0_IRQn);

  NVIC_EnableIRQ(UART0_IRQn);

  /* write_app_to_flash(). */
  if (Read_Pin(GPIOC, SW1_PORTC3) == 0U)
  {
    while (n--)
    {
      ;
    }

    if (Read_Pin(GPIOC, SW1_PORTC3) == 0U)
    {
      Erase_Multi_Sector(0xA000, 4);
      UART0_HAL_TransmitString("--START--\n");
      write_app_to_flash();
    }

  }
  else if (Read_FlashAddress(0x0000A004) != 0xFFFFFFFF)
  {
    BOOT_User_App();
  }
  else
  {
    UART0_HAL_TransmitString(" <!>: NO APPS LOADED TO CHIP\n");
  }

  while (1)
  {
    ;
  }
}

void write_app_to_flash(void)
{

  get_line_data_t get_data;

  uint8_t srec_state = true;

  uint8_t end_of_file = false;

  char *queue_front_addr = NULL;

  while ((srec_state == true) && (!end_of_file))
  {

    while (is_queue_empty())
    {
      ;
    }

    queue_front_addr = get_front_address();

    srec_state = srec_parser(queue_front_addr, &get_data, &end_of_file);

    if (srec_state == true)
    {
      pop_data_from_queue();
      BOOT_Write_App_To_Flash(get_data.address, get_data.data, get_data.byte_count - 3);
    }
    else
    {
      UART0_HAL_TransmitString("!<FILE ERROR>");
    }
  }

  UART0_HAL_TransmitString("FINISH!");

}

void Get_Data(void)
{
  if (ptr == NULL)
  {
    ptr = get_rear_address();
  }

  re_data = UART0_HAL_ReceiveData();

  if (re_data != '\n')
  {

    *(ptr + i) = re_data;
    ++i;
  }
  else
  {
    *(ptr + i) = re_data;
    push_data_to_queue();
    i = 0;
    ptr = NULL;
  }
}
