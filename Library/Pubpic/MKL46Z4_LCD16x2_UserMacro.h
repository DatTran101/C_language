/*
********************************************************************************
* @file     MKL46Z4_LCD_USERMACRO.h
* @author   DatTK2
* @version  V1
* @date     2, Jan 2023
******************************************************************************/

#ifndef _MKL46Z4_LCD_USERMACRO_H
#define _MKL46Z4_LCD_USERMACRO_H


/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4_GPIO_DRV.h"


/*******************************************************************************
   Defination, Macro
 ******************************************************************************/

/* Define LCD pins connected to MCU's GPIO pins */
#define RS_GPIO GPIOE
#define RS_PORT PORTE
#define RS_PIN  PIN_22

#define RW_GPIO GPIOE
#define RW_PORT PORTE
#define RW_PIN  PIN_21

#define E_GPIO  GPIOE
#define E_PORT  PORTE
#define E_PIN   PIN_20

#define D0_GPIO GPIOE
#define D0_PORT PORTE
#define D0_PIN  PIN_2

#define D1_GPIO GPIOE
#define D1_PORT PORTE
#define D1_PIN  PIN_3

#define D2_GPIO GPIOE
#define D2_PORT PORTE
#define D2_PIN  PIN_6

#define D3_GPIO GPIOE
#define D3_PORT PORTE
#define D3_PIN  PIN_16

#define D4_GPIO GPIOE
#define D4_PORT PORTE
#define D4_PIN  PIN_17

#define D5_GPIO GPIOE
#define D5_PORT PORTE
#define D5_PIN  PIN_18

#define D6_GPIO GPIOE
#define D6_PORT PORTE
#define D6_PIN  PIN_19

#define D7_GPIO GPIOE
#define D7_PORT PORTE
#define D7_PIN  PIN_31


#endif