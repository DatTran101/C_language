/*
********************************************************************************
* @file     MKL46Z4_SYSTEMTICK_DRV.h
* @author   DatTK2
* @version  V1
* @date     10, Jan 2023
*******************************************************************************/

#ifndef _MKL46Z4_SystemTick_DRV_H_
#define _MKL46Z4_SystemTick_DRV_H_


/*******************************************************************************
  Includes
*******************************************************************************/

#include "MKL46Z4_SystemTick_HAL.h"
#include <stdint.h>


/*******************************************************************************
   Defination, Macro
*******************************************************************************/

/* Value definition for software Timer. */
#define SWTIMER_0    0U
#define SWTIMER_1    1U
#define SWTIMER_2    2U
#define SWTIMER_3    3U
#define SWTIMER_4    4U
#define SWTIMER_5    5U
#define SWTIMER_6    6U
#define SWTIMER_7    7U
#define SWTIMER_8    8U
#define SWTIMER_9    9U


#define SWTIMER_NUMBERS 10U             /* number of software timers generated. */

#define SWTIMER_ENABLE  1U              /* SWTIMER_ENABLE has a value of 1. */
#define SWTIMER_DISABLE 0U              /* SWTIMER_DISABLE has a value of 0. */

/**
 * @brief This macro used to reate a callback function.
 *
 * @param
 */
typedef void (*UserFunc_CallBack)(void);

/*!
 * @brief Structure for the sofware timer
 *
 * Defines the elements of the software timer.
 */
typedef struct
{
    uint32_t counter;
    uint32_t reCounter;
    uint8_t  state;
    UserFunc_CallBack func_calledBack;
} SWTimer_t;


/*******************************************************************************
  API Prototype
*******************************************************************************/

/**
 * @brief This Function used to init System tick.
 * @param
 *
 */
void SystemTick_DRV_Init();

/**
 * @brief This Function used to enable software timer x.
 * @param Software timer x.
 *
 */
void SystemTick_DRV_Enable(uint8_t SWTimer_x);

/**
 * @brief This Function used to disable software timer x.
 * @param Software timer x.
 *
 */
void SystemTick_DRV_Disable(uint8_t SWTimer_x);

/**
 * @brief This Function used to set alarm for system tick.
 * @param 1:  Software timer x.
 * @param 2:  Time for the software timer in milliseconds.
 */
void SystemTick_DRV_SetAlarm_ms(uint8_t SWTimer_x, uint32_t time_ms);

/**
 * @brief This Function used to Allows the user to call a user-defined function 
 * corresponding to the selected software timer.
 *
 * @param 1:  Software timer x.
 * @param 2:  Address of the function the user wants to call.
 */
void SystemTick_DRV_RegisterCallBack(uint8_t SWTimer_x, UserFunc_CallBack func_name);


#endif /* __MKL46Z4_DRV_SWTIMER_h__ */

