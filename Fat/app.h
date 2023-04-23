/********************************************************************************
* @file    app.h
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions for implementing with the FAT file system
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _APP_H_
#define _APP_H_
#include "fat.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

typedef struct
{
    uint8_t day;                        /* Save day information from bit 0 to bit 4 of field last write date. */
    uint8_t month;                      /* Save month information from bit 5 to bit 8 of field last write date. */
    uint32_t year;                      /* Save year information from bit 9 to bit 15 of field last write date. */
    uint8_t hour;                       /* Save hour information from bit 11 to bit 15 of field last write time. */
    uint8_t minute;                     /* Save minute information from bit 5 to bit 10 of field last write time. */
}app_date_modified_t;

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/* Get value of disk. */
/* Return result: 1 is successful, 0 is faild */
uint8_t informatiomDisk(void);

/* Information proccess root directory. */
/* Paramater: pointer type fat_collection_root_t. */
void informationProccessRoot(fat_collection_root_t *listOfRoot);

/* Print root directory list. */
/* Paramater: pointer type fat_collection_root_t. */
void printRootList(fat_collection_root_t *listOfRoot);

/* Information proccess sub directory. */
/* Paramater: pointer type fat_collection_root_t. */
void informationProccessSub(fat_collection_root_t *listOfRoot);

/* Print sub directory list. */
/* Paramater: pointer type fat_collection_root_t. */
void printSubList(fat_collection_root_t *listOfSub);

/* Print file list. */
/* Paramater: pointer type fat_collection_file_t. */
void printFileList(fat_collection_file_t *listOfFile);

/* Display to the screen and the user's actions. */
void opption(void);

/* Check if the entered value is valid or invailid. */
/* Paramater: pointer type fat_collection_root_t. */
/* Return the input value. */
int16_t checkScanChoice(fat_collection_root_t *rootList);

/* Delete the value stored in the terminal.*/
void clearSdtin(void);

#endif