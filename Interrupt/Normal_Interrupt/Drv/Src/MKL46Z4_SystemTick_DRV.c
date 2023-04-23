/*
********************************************************************************
* @file     MKL46Z4_GPIO_DRV.c
* @author   DatTK2
* @version  V1
* @date     10, Jan 2023
*******************************************************************************/


/*******************************************************************************
  Includes
*******************************************************************************/
#include "MKL46Z4_SystemTick_DRV.h"
#include <stdlib.h>


/*******************************************************************************
   Defination, Macro
*******************************************************************************/

/* Array whose number of elements is the number of software timers, data type is SWTimer_t. */
static SWTimer_t SWTimer[SWTIMER_NUMBERS];

/* The variable that stores the address of the function. */
UserFunc_CallBack func_name;


/*******************************************************************************
  API Prototype
*******************************************************************************/

/**
 * @brief This Function used to create delay for software timer with units of milliseconds.
 * @param
 */
static void SystemTick_DRV_CreateDelay_ms(void);


/*******************************************************************************
  API 
*******************************************************************************/

static void SystemTick_DRV_CreateDelay_ms(void)
{
  /* Variable is a software timer. */
  uint8_t SWTimer_x = 0;
  
  /* Loop through all software timers. */
  for(SWTimer_x = 0; SWTimer_x < SWTIMER_NUMBERS; SWTimer_x ++)
  {
    
    /* Check the condition of each software timer, if the software timer meets the condition, set the time. */
    if(SWTimer[SWTimer_x].func_calledBack != NULL &&  SWTimer[SWTimer_x].state == SWTIMER_ENABLE)
    {
      /* Decrease the counter by 1 unit, which corresponds to creating a delay of 1 millisecond. */
      SWTimer[SWTimer_x].counter--;
      
      
      if(SWTimer[SWTimer_x].counter == 0)
      {
        /* Call a function whose address has been passed in by the user. */
        SWTimer[SWTimer_x].func_calledBack();
        
        /* Reset the counter value. */
        SWTimer[SWTimer_x].counter = SWTimer[SWTimer_x].reCounter;
          
      }
      
    }
    
  }
  
}


void SystemTick_DRV_Enable(uint8_t SWTimer_x)
{
  /* Enable the corresponding software timer. */
  SWTimer[SWTimer_x].state = SWTIMER_ENABLE;
    
}


void SystemTick_DRV_Disable(uint8_t SWTimer_x)
{
  /* Enable the corresponding software timer. */
  SWTimer[SWTimer_x].state = SWTIMER_DISABLE;
}


void SystemTick_DRV_RegisterCallBack(uint8_t SWTimer_x, UserFunc_CallBack func_name)
{
  /* Store the address of the function passed in by the user. */
  SWTimer[SWTimer_x].func_calledBack = func_name;
}

void SystemTick_DRV_SetAlarm_ms(uint8_t SWTimer_x, uint32_t time_ms)
{
  /* Set the initial value for the counter. */
  SWTimer[SWTimer_x].counter = time_ms;
  
  /* Set the value for the recounter. */
  SWTimer[SWTimer_x].reCounter = time_ms;
  
}

void SystemTick_DRV_Init()
{
  /* Pass the address of the function down to the HAL  layer */
  SystemTick_HAL_RegisterCallBack(SystemTick_DRV_CreateDelay_ms);
  
  /* Initialize parameters and operating conditions for the system tick. */
  SystemTick_HAL_Init();
  
}
