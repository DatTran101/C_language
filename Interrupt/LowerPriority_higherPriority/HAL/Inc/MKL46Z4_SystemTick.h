
#ifndef _MKL46Z4_SYSTEMTICK_HAL_H_
#define _MKL46Z4_SYSTEMTICK_HAL_H_

// #include "core_cm0plus.h"
#include "MKL46Z4.h"

typedef void (*Set_SWTimer_CallBack)(void);

void SystemTick_HAL_Init();

// void SystemTick_HAL_SetTime(uint32_t SWTimer_time);

void SystemTick_HAL_RegisterCallBack(Set_SWTimer_CallBack func_name);

#endif
