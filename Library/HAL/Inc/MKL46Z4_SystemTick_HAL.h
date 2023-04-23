
/*
********************************************************************************
* @file     MKL46Z4_SystemTick_HAL.h
* @author   DatTK2
* @version  V1
* @date     10, Jan 2023
*******************************************************************************/


#ifndef _MKL46Z4_SYSTEMTICK_HAL_H_
#define _MKL46Z4_SYSTEMTICK_HAL_H_


/*******************************************************************************
  Includes
*******************************************************************************/

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

typedef void (*Set_SWTimer_CallBack)(void);

void SystemTick_HAL_Init();

//void SystemTick_HAL_SetTime(uint32_t SWTimer_time);

void SystemTick_HAL_RegisterCallBack(Set_SWTimer_CallBack func_name);


#endif
