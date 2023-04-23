/*
********************************************************************************
* @file     MKL46Z4_PIT_DRV.h
* @author   DatTK2
* @version  V1
* @date     16, Jan 2023
*******************************************************************************/


/*******************************************************************************
  Includes
*******************************************************************************/

#ifndef __MKL46Z4_PIT_DRV_H__
#define __MKL46Z4_PIT_DRV_H__

typedef void (*PIT_UserFunc_CallBack) (void);

/**
 * @brief Initialize PIT.
 */
void PIT_DRV_Init(void);

/**
 * @brief Set enble PIT.
 */
void PIT_DRV_Enable(void);

/**
 * @brief Set disable PIT.
 */
void PIT_DRV_Disable();



/**
 * @brief This Function used to Allows the user to call a user-defined function. 
 *
 * @param:  Address of the function the user wants to call.
 */
void PIT_DRV_RegisterCallback(PIT_UserFunc_CallBack func_namefunc_name);

/**
 * @brief Deinitialize PIT.
 */
void PIT_DRV_Deinit(void);

#endif /* __MKL46Z4_PIT_DRV__H__ */
