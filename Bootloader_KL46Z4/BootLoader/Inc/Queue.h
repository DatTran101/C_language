
/*
********************************************************************************
* @file     Queue.h
* @author   DatTK2
* @version  V1
* @date     15, Feb 2023
*******************************************************************************/


#ifndef __QUEUE_H__
#define __QUEUE_H__


/*******************************************************************************
 * Includes
*******************************************************************************/

#include <stdint.h>


/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define MAX_ELEMENT     4U          /* The maximum numbers of elements of the queue. */
#define DATA            518U        /* The maximum characters of line of srec file. */
#define true            1U
#define false           0U


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief  This Function used to check empty of queue data
 *
 * @return Return queue state.
 *         if queue is empty: return true.
 *         if queue is not empty: return false.
 */
uint8_t is_queue_empty(void);

/**
 * @brief  This Function used to check full of queue data
 *
 * @return Return queue state.
 *         if queue is full: return true.
 *         if queue is not full: return false.
 */
uint8_t is_queue_full(void);

/**
 * @brief  This Function used to push data to the last position in queue data
 *
 * @return Return true if push to queue successfull
 *         Return false if push to queue unsuccessfull
 */
void push_data_to_queue(void);

/**
 * @brief  This Function used to pop data from the first position in queue data
 *
 * @return Return true if pop from queue successfull
 *         Return false if pop from queue unsuccessfull
 */
void pop_data_from_queue(void);

/**
 * @brief  This Function used to get address rear of queue
 *
 * @return Return address rear of queue data
 */
char *get_rear_address(void);

/**
 * @brief  This Function used to get address front of queue
 *
 * @return Return address front of queue data
 */
char *get_front_address(void);

#endif /*_QUEUE_COMMON_H_*/

/**End of file**/