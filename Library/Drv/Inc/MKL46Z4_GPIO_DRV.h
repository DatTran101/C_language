/*
********************************************************************************
* @file     MKL46Z4_GPIO_DRV.h
* @author   DatTK2
* @version  V1
* @date     31, Dec 2022
*******************************************************************************/

#ifndef _MKL46Z4_FGPIO_DRV_H_
#define _MKL46Z4_FGPIO_DRV_H_

/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4.h"
#include "MKL46Z4_GPIO_HAL.h"


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

typedef enum
{
  PORT_A = SIM_SCGC5_PORTA_SHIFT,
  PORT_B = SIM_SCGC5_PORTB_SHIFT,
  PORT_C = SIM_SCGC5_PORTC_SHIFT,
  PORT_D = SIM_SCGC5_PORTD_SHIFT,
  PORT_E = SIM_SCGC5_PORTE_SHIFT,

} SCGC5_mode_e;

typedef enum
{
  Analog = 0,
  GPIO = 1,
  Atl2 = 2,
  Atl3 = 3,
} MUX_Config_e;

typedef enum
{
  PIN_0 = 0U,
  PIN_1 = 1U,
  PIN_2 = 2U,
  PIN_3 = 3U,
  PIN_4 = 4U,
  PIN_5 = 5U,
  PIN_6 = 6U,
  PIN_7 = 7U,
  PIN_8 = 8U,
  PIN_9 = 9U,
  PIN_10 = 10U,
  PIN_11 = 11U,
  PIN_12 = 12U,
  PIN_13 = 13U,
  PIN_14 = 14U,
  PIN_15 = 15U,
  PIN_16 = 16U,
  PIN_17 = 17U,
  PIN_18 = 18U,
  PIN_19 = 19U,
  PIN_20 = 20U,
  PIN_21 = 21U,
  PIN_22 = 22U,
  PIN_23 = 23U,
  PIN_24 = 24U,
  PIN_25 = 25U,
  PIN_26 = 26U,
  PIN_27 = 27U,
  PIN_28 = 28U,
  PIN_29 = 29U,
  PIN_30 = 30U,
  PIN_31 = 31U,

} PINx_e;


/*******************************************************************************
* Global variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief This Function used to init clock for corresponding mode at
 * System Clock Gating Control Register 5.
 * @param
 * Param: mode at System Clock Gating Control Register 5.
 */
void GPIO_DRV_Init(SCGC5_mode_e SCGC5_mode);

/**
 * @brief This Function used to enable MUX field
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what starting position of corresponding field.
 * Param3: Status of corresponding field or mode of corresponding.
 */
void GPIO_DRV_EnableMUX(PORT_Type *PORTx, PINx_e PINx, MUX_Config_e status);

/**
 * @brief This Function used to disable MUX field of Pin Control Register
 *
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what starting position of corresponding field.
 * Param3: Status of corresponding field or mode of corresponding.
 */
void GPIO_DRV_DisableMUX(PORT_Type *PORTx, PINx_e PINx);

/**
 * @brief This Function used to enable "pull mode".
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what position of pull selection field.
 */
void GPIO_DRV_EnablePull(PORT_Type *PORTx, PINx_e PINx);

/**
 * @brief This Function used to disable "pull mode".
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what position of pull selection field.
 */
void GPIO_DRV_DisablePull(PORT_Type *PORTx, PINx_e PINx);

/**
 * @brief This Function used to config pullup internal resistor.
 *
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what position of pull select field.
 */
void GPIO_DRV_Pullup(PORT_Type *PORTx, PINx_e PINx);

/**
 * @brief This Function used to config pulldown internal resistor.
 *
 * @param
 * Param1: PORT_Type pointer point to the corresponding port's register.
 * Param2: A pin, what position of pull select field.
 */
void GPIO_DRV_PullDown(PORT_Type *PORTx, PINx_e PINx);

/**
 * @brief This Function used to config Pin is output.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: PORT_Type pointer point to the corresponding PORTx's register.
 * Param3: Position of corresponding pin.
 */
void GPIO_DRV_Config_Output(GPIO_Type *GPIOx, PORT_Type *PORTx, PINx_e PINx);

/**
 * @brief This Function used to config 1 Pin is high level output.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: Position of corresponding pin.
 */
void GPIO_DRV_Write1Pin(GPIO_Type *GPIOx, PINx_e PINx, PINx_State_e state);

///**
// * @brief This Function used to config 1 Pin is low level output.
// * @param
// * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
// * Param2: Position of corresponding pin.
// */
//void GPIO_DRV_Write1Pin_LowLevel(GPIO_Type *GPIOx, PINx_e PINx);

/**
 * @brief This Function used to config many Pins are high level output.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: PORT_Type pointer point to the corresponding PORTx's register.
 * Param3: Position of corresponding pins.
 */
void GPIO_DRV_Write_PINs_HighLevel(GPIO_Type *GPIOx, PORT_Type *PORTx, uint32_t PINs);

/**
 * @brief This Function used to config many Pins are low level output.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: PORT_Type pointer point to the corresponding PORTx's register.
 * Param3: Position of corresponding pins.
 */
void GPIO_DRV_Write_PINs_LowLevel(GPIO_Type *GPIOx, PORT_Type *PORTx, uint32_t PINs);

/**
 * @brief This Function used to config Pin is tongle output.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: Position of corresponding pin.
 */
void GPIO_DRV_Toggle(GPIO_Type *GPIOx, PINx_e PINx);

/**
 * @brief This Function used to config Pin is input.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: PORT_Type pointer point to the corresponding PORTx's register.
 * Param3: Position of corresponding pin.
 */
void GPIO_DRV_Config_Input(GPIO_Type *GPIOx, PORT_Type *PORTx, PINx_e PINx);

/**
 * @brief This Function used to Read  value of corresponding pin and return
 * this value.
 * @param
 * Param1: GPIO_Type pointer point to the corresponding GPIOx's register.
 * Param2: Position of corresponding pin.
 */
uint8_t GPIO_DRV_Read_PIN(GPIO_Type *GPIOx, PINx_e PINx);

/**
 * @brief This Function used to deinit clock for corresponding mode at
 * System Clock Gating Control Register 5.
 * @param
 * Param: mode at System Clock Gating Control Register 5.
 */
void GPIO_DRV_DeInit(SCGC5_mode_e SCGC5_mode);

#endif /*_MKL46Z4_GPIO_DRV_H_*/