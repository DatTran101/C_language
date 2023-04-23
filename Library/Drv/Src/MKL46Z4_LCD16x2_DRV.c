/*
********************************************************************************
* @file     MKL46Z4_GPIO_DRV.c
* @author   DatTK2
* @version  V1
* @date     4, Jan 2023
*******************************************************************************/


/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4_LCD16x2_DRV.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define LCD_PIN_MASK    0x01U
#define D0_PIN_SHIFT    0x00U
#define D1_PIN_SHIFT    0x01U
#define D2_PIN_SHIFT    0x02U
#define D3_PIN_SHIFT    0x03U
#define D4_PIN_SHIFT    0x04U
#define D5_PIN_SHIFT    0x05U
#define D6_PIN_SHIFT    0x06U
#define D7_PIN_SHIFT    0x07U


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief This Function used to configure RS pin of LCD.
 * @param
 * Param: state of pin.
 */
static void RS_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to configure RW pin of LCD.
 * @param
 * Param: state of pin.
 */
static void RW_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to configure enable pin of LCD.
 * @param
 * Param: state of pin.
 */
static void E_PIN_Config(void);

/**
 * @brief This Function used to write state 0 or 1 to D0 pin of LCD.
 * @param
 * Param: state of pin.
 */
static void D0_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to write state 0 or 1 to D1 pin of LCD.
 * @param
 * Param: state of pin.
 */
static void D1_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to write state 0 or 1 to D2 pin of LCD.
 * @param
 * Param: state of pin.
 */
static void D2_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to write state 0 or 1 to D3 pin of LCD.
 * @param
 * Param: state of pin.
 */
static void D3_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to write state 0 or 1 to D4 pin of LCD.
 * @param
 * Param: state of pin.
 */
static void D4_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to write state 0 or 1 to D5 pin of LCD.
 * @param
 * Param: state of pin.
 */
static void D5_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to write state 0 or 1 to D6 pin of LCD.
 * @param
 * Param: state of pin.
 */
static void D6_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to write state 0 or 1 to D7 pin of LCD.
 * @param
 * Param: state of pin.
 */
static void D7_PIN_Config(PINx_State_e state);

/**
 * @brief This Function used to re-Show string.
 * @param
 * Param: Error content.
 */
static void LCD16x2_ReShowStr(char* string );

/**
 * @brief This Function used to display error.
 * @param
 * Param: Error content.
 */
static void LCD16x2_ShowError(const char* string );

/**
 * @brief This Function used to create delay with units of microseconds.
 * @param
 * Param: Times delay.
 */
static void delay_us(uint32_t n);


/*******************************************************************************
  API
*******************************************************************************/

static void RS_PIN_Config(PINx_State_e state)
{
  GPIO_DRV_Write1Pin(RS_GPIO, RS_PIN, state);           /* Write state 0 or 1 to RS pin of LCD. */
}

static void RW_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(RW_GPIO, RW_PIN, state);           /* Write state 0 or 1 to RW pin of LCD */

}

static void E_PIN_Config(void)
{

  GPIO_DRV_Write1Pin(E_GPIO, E_PIN, SET);               /* Write state 1 to enable pin of LCD to start pulse generation on enable pin. */
  GPIO_DRV_Write1Pin(E_GPIO, E_PIN, RESET);             /* Write state 0 to enable pin of LCD to complete pulse generation on enable pin. */

}

static void D0_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(D0_GPIO, D0_PIN, state);            /* Write state 0 or 1 to D0 pin of LCD */
}

static void D1_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(D1_GPIO, D1_PIN, state);           /* Write state 0 or 1 to D1 pin of LCD */
}

static void D2_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(D2_GPIO, D2_PIN, state);           /* Write state 0 or 1 to D2 pin of LCD */
}

static void D3_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(D3_GPIO, D3_PIN, state);           /* Write state 0 or 1 to D3 pin of LCD */
}

static void D4_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(D4_GPIO, D4_PIN, state);           /* Write state 0 or 1 to D4 pin of LCD */
}

static void D5_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(D5_GPIO, D5_PIN, state);           /* Write state 0 or 1 to D5 pin of LCD */
}

static void D6_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(D6_GPIO, D6_PIN, state);           /* Write state 0 or 1 to D6 pin of LCD */
}

static void D7_PIN_Config(PINx_State_e state)
{

  GPIO_DRV_Write1Pin(D7_GPIO, D7_PIN, state);           /* Write state 0 or 1 to D7 pin of LCD */
}

static void delay_us(uint32_t n)
{
  uint32_t i = 0;
  uint16_t j = 0;
  for( j = 0; j < 2; j ++)
  {
    /* The loop generates a delay, with each loop generating a delay of 1 microsecond */
    for( i = 0; i < n; i++)
    {
      __asm("nop");
    }
  }
}


void LCD16x2_DRV_Init()
{

  /* Configure output for the GPIO pins connected to the corresponding LCD pins */
  GPIO_DRV_Config_Output(RS_GPIO, RS_PORT, RS_PIN);
  GPIO_DRV_Config_Output(RW_GPIO, RW_PORT, RW_PIN);
  GPIO_DRV_Config_Output(E_GPIO, E_PORT, E_PIN);
  GPIO_DRV_Config_Output(D0_GPIO, D0_PORT, D0_PIN);
  GPIO_DRV_Config_Output(D1_GPIO, D1_PORT, D1_PIN);
  GPIO_DRV_Config_Output(D2_GPIO, D2_PORT, D2_PIN);
  GPIO_DRV_Config_Output(D3_GPIO, D3_PORT, D3_PIN);
  GPIO_DRV_Config_Output(D4_GPIO, D4_PORT, D4_PIN);
  GPIO_DRV_Config_Output(D5_GPIO, D5_PORT, D5_PIN);
  GPIO_DRV_Config_Output(D6_GPIO, D6_PORT, D6_PIN);
  GPIO_DRV_Config_Output(D7_GPIO, D7_PORT, D7_PIN);

  delay_ms(60);                                 /* Wait for more than 40ms after Vcc rises to 2.7v. */

  LCD16x2_SendCommand(LCD_INIT);                /* Send LCD initialization command for the 1rd time. */
  delay_ms(8);                                  /* LCD needs more than 4.1ms to execute this command. */

  LCD16x2_SendCommand(LCD_INIT);                /* Send LCD initialization command for the 2rd time. */
  delay_us(160);                                /* LCD needs more than 100us to execute this command. */

  LCD16x2_SendCommand(LCD_INIT);                /* Send LCD initialization command for the 3rd time. */
  delay_us(160);                                /* LCD needs more than 100us to execute this command. */

  LCD16x2_SendCommand(ACTIVATE_SECOND_LINE);    /* LCD activate 2-line display mode. */

  LCD16x2_SendCommand(TWO_LINE_AND_5X7_MATRIX); /* LCD activate 2-line and 5x7 matrix display mode. */

  LCD16x2_SendCommand(DISTLAY_ON_CURSOR_OFF);   /* Turn on the LCD screen and turn off the cursor display */

  LCD16x2_DRV_Clear();                          /* Clear the content displayed on the LCD screen. */

}

void LCD16x2_DRV_Clear()
{
  LCD16x2_SendCommand(CLEAR_DISPLAY_SCREEN);    /* Clear the content displayed on the LCD screen. */
  delay_ms(2);                                  /* LCD needs less than 1,64ms to execute this command. */

}

void LCD16x2_DRV_GotoXY(uint8_t x, uint8_t y)
{
  /*
    Check the condition and return the cursor to row 1
    y is column position and must be less than 16
 */
  if((0 == x) & (y < 16))
  {
    /* Place the cursor in row 1 and column y */
    LCD16x2_SendCommand(CURSOR_TO_BEGINNING_OF_FIRST_LINE + y);
  }
  /*
    Check the condition and return the cursor to row 2
    y is column position and must be less than 16
 */
  else if((1 == x) & (y < 16))
  {
    /* Place the cursor in row 2 and column y */
    LCD16x2_SendCommand(CURSOR_TO_BEGINNING_OF_SECOND_LINE + y);
  }
  /*
  In case the input exceeds the allowed range of the screen cursor,
  error message on the screen.
  */
  else
  {
      while(1)
      {
      LCD16x2_DRV_Clear();
      delay_ms(1000);
      LCD16x2_SendCommand(CURSOR_TO_BEGINNING_OF_FIRST_LINE);           /* Move the screen cursor to the beginning of row 1. */
      LCD16x2_ShowError("Cursor is out of");                            /* Show 1 part of error message on row 1. */
      LCD16x2_SendCommand(CURSOR_TO_BEGINNING_OF_SECOND_LINE + 2);      /* Move the screen cursor to the beginning of row 2. */
      LCD16x2_ShowError("the range");                                   /* Show the rest of error message on row 2. */
      delay_ms(3000);
      }
  }
}

void LCD16x2_SendCommand(uint8_t cmd)
{
  /* Set RS = 0 and RW = 0 to prepare for sending command to the Instruction Register. */
  RS_PIN_Config(RESET);
  RW_PIN_Config(RESET);

  /* Separates the bits of command and feeds it to the corresponding LCD pins. */
  D0_PIN_Config((PINx_State_e)(cmd>>D0_PIN_SHIFT & LCD_PIN_MASK));
  D1_PIN_Config((PINx_State_e)(cmd>>D1_PIN_SHIFT & LCD_PIN_MASK));
  D2_PIN_Config((PINx_State_e)(cmd>>D2_PIN_SHIFT & LCD_PIN_MASK));
  D3_PIN_Config((PINx_State_e)(cmd>>D3_PIN_SHIFT & LCD_PIN_MASK));
  D4_PIN_Config((PINx_State_e)(cmd>>D4_PIN_SHIFT & LCD_PIN_MASK));
  D5_PIN_Config((PINx_State_e)(cmd>>D5_PIN_SHIFT & LCD_PIN_MASK));
  D6_PIN_Config((PINx_State_e)(cmd>>D6_PIN_SHIFT & LCD_PIN_MASK));
  D7_PIN_Config((PINx_State_e)(cmd>>D7_PIN_SHIFT & LCD_PIN_MASK));

  /* Enable the process to send commands to the Instruction Register. */
  E_PIN_Config();

  /* LCD needs less than 40us to to send command to the instruction register. */
  delay_us(40);

}

void LCD16x2_DRV_WriteChar(unsigned char chr)
{
  /* Set RS = 1 and RW = 0 to prepare for sending command to the Data Register. */
  RS_PIN_Config(SET);
  RW_PIN_Config(RESET);

  /* Separates the bits of data and feeds it to the corresponding LCD pins. */
  D0_PIN_Config((PINx_State_e)(chr>>D0_PIN_SHIFT & LCD_PIN_MASK));
  D1_PIN_Config((PINx_State_e)(chr>>D1_PIN_SHIFT & LCD_PIN_MASK));
  D2_PIN_Config((PINx_State_e)(chr>>D2_PIN_SHIFT & LCD_PIN_MASK));
  D3_PIN_Config((PINx_State_e)(chr>>D3_PIN_SHIFT & LCD_PIN_MASK));
  D4_PIN_Config((PINx_State_e)(chr>>D4_PIN_SHIFT & LCD_PIN_MASK));
  D5_PIN_Config((PINx_State_e)(chr>>D5_PIN_SHIFT & LCD_PIN_MASK));
  D6_PIN_Config((PINx_State_e)(chr>>D6_PIN_SHIFT & LCD_PIN_MASK));
  D7_PIN_Config((PINx_State_e)(chr>>D7_PIN_SHIFT & LCD_PIN_MASK));

  /* Enable the process to send commands to the Instruction Register. */
  E_PIN_Config();

}

void LCD16x2_DRV_WriteString(char *string)
{
  uint8_t i = 0;    /* Variable "i" is used to display the i.th character in the string */

  if( strlen(string) > 16)
  {
    while(1)
    {
      LCD16x2_DRV_Clear();
      delay_ms(1000);
      LCD16x2_DRV_GotoXY(0,0);
      LCD16x2_ReShowStr(string);                  /* At line 1 show the string again. */
      LCD16x2_DRV_GotoXY(1,0);
      LCD16x2_ShowError("Str is too long!");      /* At line 2, the error message is displayed. */

      delay_ms(3000);
    }

  }
  /* If "i" is still smaller than the string length, print to the LCD the i.th character. */
  for(i = 0; i < strlen(string); i++ )
  {
    LCD16x2_DRV_WriteChar(string[i]);
  }
}

static void LCD16x2_ReShowStr(char* string )
{
  uint8_t i = 0;        /* Variable "i" is used to display the i.th character in the string. */

  /* Display 16 characters on LCD screen. */
  for(i = 0; i < 16; i++ )
  {

    /* Display the first 13 characters of the string. */
    if( i < 13)
    {
      LCD16x2_DRV_WriteChar(string[i]);
    }
    /* Display 3 dots, string description is too long. */
    else
    {
      LCD16x2_DRV_WriteChar('.');
    }

  }

}

static void LCD16x2_ShowError(const char* string)
{

  uint8_t i = 0;

  for(i = 0; i < strlen(string); i++ )
  {
    LCD16x2_DRV_WriteChar(string[i]);
  }
}

void delay_ms(uint32_t n)
{
  uint16_t i = 0;
  uint32_t j = 0;
  /* The delay function uses the system default frequency of about 20MHz. */
  for( i = 0; i < 2000; i ++)
  {
    for( j = 0; j < n; j ++)
    {
      __asm("nop");
    }

  }

}



