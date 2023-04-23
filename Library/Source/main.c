/*
********************************************************************************
* @file     main.c
* @author   DatTK2
* @version  V1
* @date     9, Feb 2023
*******************************************************************************/


/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4.h"
#include "MKL46Z4_GPIO_DRV.h"
#include "MKL46Z4_UART0_DRV.h"


/*******************************************************************************
   Defination, Macro
*******************************************************************************/

/* Define pin name for green led and red led */
#define GREEN_LED_PORTD5 PIN_5
#define RED_LED_PORTE29 PIN_29

/* Define pin name for UART0 TX. */
#define UART0_RX PIN_1
#define UART0_TX PIN_2

/* Define string lenght for strings what use to reference. */
#define NULL_CHARACTER 1U                               /* Null character in every string. */
#define STRLEN_GREEN_ON (8U + NULL_CHARACTER)           /* string green_on include 8 character and 1 null character. */
#define STRLEN_GREEN_OFF (9U + NULL_CHARACTER)          /* string green_off include 9 character and 1 null character. */
#define STRLEN_RED_ON (6U + NULL_CHARACTER)             /* string red_on include 6 character and 1 null character. */
#define STRLEN_RED_OFF (7U + NULL_CHARACTER)            /* string red_off include 7 character and 1 null character. */
#define MAX_LEN 12U


/*******************************************************************************
  Global Variable
*******************************************************************************/

static char get_data;                   /* Get data from return value of function. */
static uint8_t index = 0U;              /* Index for buffer. */
static char buffer[15] = {0};           /* Store data what received from PC. */
static char buffer_upper[11] = {0};     /* Store data what ware uppered from buffer. */

static char green_on[STRLEN_GREEN_ON] = "GREEN_ON";     /* String use to reference when turn on green led. */
static char green_off[STRLEN_GREEN_OFF] = "GREEN_OFF";  /* String use to reference when turn off green led. */
static char red_on[STRLEN_RED_ON] = "RED_ON";           /* String use to reference when turn on red led. */
static char red_off[STRLEN_RED_OFF] = "RED_OFF";        /* String use to reference when turn off red led. */


/*******************************************************************************
  Function Prototype
*******************************************************************************/


/**
 * @brief This Function used to upper character.
 *
 * @param 
 */
static char charUpper(char chr);

/**
 * @brief This Function used to upper string.
 *
 * @param 
 */
static void strUpper();

/**
 * @brief This Function used to compare 2 string.
 *
 * @param 1: String 1 what getted from PC and affer uppered.
 * @param 2: String 2 is string reference.
 * @param 3: Lenght of string 2.
 */
static uint8_t StrCompare(char *str1, char *str2, uint8_t len);

/**
 * @brief This Function used to get data when interrupt of UART0 occur.
 *
 * @param 
 */
static void GetData(void); 

/**
 * @brief This Function used to control red led and green led.
 *
 * @param 
 */
static void Control_Led(void);
/*******************************************************************************
   Code
*******************************************************************************/


int main(void)
{
  /* Configure condition for green led. */
  GPIO_DRV_Init(PORT_D);
  GPIO_DRV_Config_Output(GPIOD, PORTD, GREEN_LED_PORTD5);
  GPIO_DRV_Write1Pin(GPIOD, GREEN_LED_PORTD5, SET);             /* Turn off green led when start. */

   /* Configure condition for red led. */
  GPIO_DRV_Init(PORT_E);
  GPIO_DRV_Config_Output(GPIOE, PORTE, RED_LED_PORTE29);
  GPIO_DRV_Write1Pin(GPIOE, RED_LED_PORTE29, SET);              /* Turn off red led when start. */

  /* Configure PORTA 1 is UART0_RX mode. */
  GPIO_DRV_Init(PORT_A);
  GPIO_DRV_EnableMUX(PORTA, UART0_RX, Atl2);
  
  /* Configure condition for UART0, used to use UART0. */
  UART0_DRV_Init();
  UART0_DRV_SetBaudrate(115200);
  UART0_DRV_ConfigData(8U);
  UART0_DRV_ReceiverEnable(Interrupt);
  UART0_DRV_ParityDisable();
  UART0_DRV_StopBit(1U);
  UART0_DRV_ConfigMSBF(LSB);

  /* Enable IRQ for UART0. */
  NVIC_ClearPendingIRQ(UART0_IRQn);
  NVIC_EnableIRQ(UART0_IRQn);
  
  /* Pass the address of the Control_Led function . */
  UART0_DRV_RegisterCallback(Control_Led);


  while (1)
  {
    __asm("nop");
  }

} /* End main function. */


static uint8_t StrCompare(char *str1, char *str2, uint8_t len)
{
  
  uint8_t result = 0;           /* This variable use to store return value. */
  uint8_t i = 0;                /* This variable is index for array. */
  
  /* Out of loop for if i = len or 2 string have one difference character. */
  for (i = 0; i < len && (result == 0); i++)
  {
    /* Compare characters of 2 string. */
    if (str1[i] == str2[i])
    {
      result = 0;
    }
    else
    {
      /* if 2 tring have one difference character, result = 0. */
      result = 1;
    }
  }
  return result;
}

static char charUpper(char chr)
{
  /* Check if the characters are alphabet or not. */
  if ('a' <= chr && chr <= 'z')
  {
    /* Convert to uppercase. */
    chr = chr - ((uint8_t)('a') - (uint8_t)('A'));
  }
  return chr;
}

static void strUpper()
{
  uint8_t i = 0;
  for (i = 0; i < MAX_LEN; i++)
  {
    /* Store characters into buffer_upper. */
    buffer_upper[i] = charUpper(buffer[i]);
  }
}

static void GetData(void)
{
  /* Get character when UART0 interrupt occurr. */
  get_data = UART0_DRV_ReceiveData(Interrupt);
  
  /* Compare get_data and enter character. */
  if (get_data != '\n')
  {
    /* Store get_data into buffer array. */
    buffer[index] = get_data;
    index++;
  }
  else
  {
    /* Clear index to 0 prepare for get next data. */
    index = 0;
  }
}

void Control_Led(void)
{
  /* Get data from PC. */
  GetData();
  
  /* Upper string what receive from PC. */
  strUpper();

    /* 
        Two string are the same characters, turn on green led.
        <>! Regardless of uppercase and lowercase characters.
    */
    if (0 == StrCompare(buffer_upper, green_on, STRLEN_GREEN_ON))
    {
      GPIO_DRV_Write1Pin(GPIOD, GREEN_LED_PORTD5, RESET);
    }
    
    /* 
        Two string are the same characters, turn of green led.
        <>! Regardless of uppercase and lowercase characters.
    */
    else if (0 == StrCompare(buffer_upper, green_off, STRLEN_GREEN_OFF))
    {
      GPIO_DRV_Write1Pin(GPIOD, GREEN_LED_PORTD5, SET);
    }
    
    /* 
        Two string are the same characters, turn on red led.
        <>! Regardless of uppercase and lowercase characters.
    */
    if (0 == StrCompare(buffer_upper, red_on, STRLEN_RED_ON))
    {
      GPIO_DRV_Write1Pin(GPIOE, RED_LED_PORTE29, RESET);
    }
    
    /* 
        Two string are the same characters, turn off red led.
        <>! Regardless of uppercase and lowercase characters.
    */
    else if (0 == StrCompare(buffer_upper, red_off, STRLEN_RED_OFF))
    {
      GPIO_DRV_Write1Pin(GPIOE, RED_LED_PORTE29, SET);
    }
}



