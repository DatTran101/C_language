
#ifndef _MKL46Z4_SYSTEMTICK_HAL_H_
#define _MKL46Z4_SYSTEMTICK_HAL_H_

#include "MKL46Z4.h"

typedef void (*Set_SWTimer_CallBack)(void);

void SystemTick_HAL_Init();


void SystemTick_HAL_RegisterCallBack(Set_SWTimer_CallBack func_name);

#endif
