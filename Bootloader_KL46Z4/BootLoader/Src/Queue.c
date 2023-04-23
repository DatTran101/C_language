/*
********************************************************************************
* @file     Queue.h
* @author   DatTK2
* @version  V1
* @date     15, Feb 2023
*******************************************************************************/

/*******************************************************************************
 * Includes
 *******************************************************************************/

#include "Queue.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/

static char queue_data[MAX_ELEMENT][DATA];      /* Two-dimensional array used to store data */
static volatile uint8_t s_front = 0U;           /* Variable used to store front element. */
static volatile uint8_t s_rear = 0U;            /* Variable used to store rear element. */
static volatile uint8_t s_element_counter = 0U; /* Variable used to count element. */


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

uint8_t is_queue_empty(void)
{
  uint8_t empty_state = true;

  if (s_element_counter == 0U)
  {
    empty_state = true;
  }
  else
  {
    empty_state = false;
  }

  return empty_state;
}

uint8_t is_queue_full(void)
{
  uint8_t full_state = true;

  if (s_element_counter == MAX_ELEMENT)
  {
    full_state = true;
  }
  else
  {
    full_state = false;
  }

  return full_state;
}

void push_data_to_queue(void)
{

  if (s_element_counter < MAX_ELEMENT)
  {

    s_rear++;
    /* Use the circular queue style. */
    s_rear %= MAX_ELEMENT;

    s_element_counter++;
  }
}

void pop_data_from_queue(void)
{

  if (s_element_counter > 0U)
  {

    s_front++;

    /* Use the circular queue style. */
    s_front %= MAX_ELEMENT;

    s_element_counter--;
  }
}

char *get_rear_address(void)
{
  /* Get the address of the array that is storing the information of rear element. */
  char *address = queue_data[s_rear];

  return address;
}

char *get_front_address(void)
{
  /* Get the address of the array that is storing the information of front element. */
  char *address = queue_data[s_front];

  return address;
}

/**End of file**/