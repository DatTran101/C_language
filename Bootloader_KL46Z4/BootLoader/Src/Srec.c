/*
********************************************************************************
* @file     Srec.c
* @author   DatTK2
* @version  V1
* @date     11, Feb 2023
*******************************************************************************/

/******************************************************************************
 * Includes
 *******************************************************************************/

#include "Srec.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

#define true              1U
#define false             0U

#define START_CODE_POS    0U
#define RECORD_TYPE_POS   1U
#define BYTE_COUNT_POS    2U
#define ADDRESS_POS       4U
#define DATA_POS          8U


/*******************************************************************************
* Variables
******************************************************************************/

static uint8_t g_is_line_structure_true = true;
static record_structure_t line;
static uint8_t g_ui8_i = 0;

static uint8_t is_valid_character = true;
static uint16_t g_ui16_sum = 0;
static uint8_t g_ui8_LSB = 0;


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

uint8_t srec_parser(const char *buffer, get_line_data_t *get_data, uint8_t *end_of_file)
{
  g_is_line_structure_true = true;
  g_ui8_i = 0;
  g_ui16_sum = 0;
  g_ui8_LSB = 0;

  /* Check record start. */
  line.record_start = buffer[0];
  g_is_line_structure_true &= (line.record_start == 'S');

  /* Check record type. */
  line.record_type = buffer[1];
  g_is_line_structure_true &= ((line.record_type >= '0') && (line.record_type <= '9'));
  if ('9' == line.record_type)
  {
    *end_of_file = true;
  }

  /* Get length of line. */
  g_ui8_i = 0;
  while ((buffer[g_ui8_i + 1] != '\r'))
  {
    g_ui8_i++;
  }
  line.length = g_ui8_i + 1;

  g_ui8_i = 0;

  /* Convert to hexa and get information. */
  if (g_is_line_structure_true == true)
  {

    /* Convert byte count. */
    get_data->byte_count = convert_chars_to_hex_8bit(buffer + BYTE_COUNT_POS);

    /* Convert data field. */
    for (g_ui8_i = 0; g_ui8_i < get_data->byte_count - 3; g_ui8_i++)
    {
      get_data->data[g_ui8_i] = convert_chars_to_hex_8bit(buffer + (DATA_POS + g_ui8_i * 2));
    }

    /* Convert address. */
    get_data->address = convert_chars_to_hex_16bit(buffer + ADDRESS_POS);

    /* Calculate check sum. */
    g_ui16_sum += (get_data->byte_count & 0xff);

    g_ui16_sum += (get_data->address >> 8) & 0xff;

    g_ui16_sum += get_data->address & 0xff;

    for (g_ui8_i = 0; g_ui8_i < get_data->byte_count - 3; g_ui8_i++)
    {
      g_ui16_sum += get_data->data[g_ui8_i];
    }

    g_ui8_LSB = ~(uint8_t)(g_ui16_sum & 0xff);

    get_data->check_sum = convert_chars_to_hex_8bit(buffer + (line.length - 2));

    g_is_line_structure_true &= (g_ui8_LSB == get_data->check_sum);

    g_is_line_structure_true &= (get_data->byte_count * 2 == (line.length - 4U));
  }

  return g_is_line_structure_true;
}

uint8_t convert_chars_to_hex_8bit(const char hex[2])
{
  uint8_t l = 0;
  uint8_t h = 0;

  if (hex[0] >= '0' && hex[0] <= '9')
    h = hex[0] - '0';
  else if (hex[0] >= 'A' && hex[0] <= 'F')
    h = hex[0] - 'A' + 10;

  if (hex[1] >= '0' && hex[1] <= '9')
    l = hex[1] - '0';
  else if (hex[1] >= 'A' && hex[1] <= 'F')
    l = hex[1] - 'A' + 10;

  return (uint8_t)((h << 4) | l);
}

uint16_t convert_chars_to_hex_16bit(const char hex[4])
{
  uint8_t h = convert_chars_to_hex_8bit(hex);
  uint8_t l = convert_chars_to_hex_8bit(hex + 2);

  return (uint16_t)((h << 8) | l);
}
