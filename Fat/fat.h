/********************************************************************************
* @file    fat.h
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions prototypes for the FAT file system
*******************************************************************************/

#ifndef _FAT_H_
#define _FAT_H_
#include "HAL.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

typedef enum
{
    NOT_OK = 0U,                                    /* State when doing faild. */
    ROOT_OK,                                        /* State when read root directory successful. */
    FUN_OK,                                         /* State when read funtion successful. */
    SUB_OK,                                         /* State when read sub directory successful. */
    READ_SUB,                                       /* State when opption is read sub directory. */
    READ_FILE                                       /* State when opption is read root directory. */
}state;

/* offset boot sector. */
#define BPB_BYTS_PER_SEC        (0x0BU)
#define BPB_SEC_PER_CLUS        (0x0DU)
#define BPB_RSVD_SEC_CNT        (0x0EU)
#define BPB_NUM_FATS            (0x10U)
#define BPB_ROOT_ENT_CNT        (0x11U)
#define BPB_TOT_SEC_16          (0x13U)
#define BPB_MEDIA               (0x15U)
#define BPB_FAT_SZ_16           (0x16U)

/* offset root directory. */
#define ATTRIBUTES              (0x0BU)
#define RESERVED                (0x0CU)
#define CREATION_TIME           (0x0EU)
#define CREATION_DATE           (0x10U)
#define LAST_ACCESS_DATE        (0x12U)
#define IGNORE_IN_FAT_12        (0x14U)
#define LAST_WRITE_TIME         (0x16U)
#define LAST_WRITE_DATE         (0x18U)
#define FIRST_LOGICAL_CLUSTER   (0x1AU)
#define FILE_SIZE               (0x1CU)

/* Struct stores byte information of Boot Sector. */
typedef struct
{
    uint16_t BPB_BytsPerSec;                        /* Bytes per sector. */
    uint8_t BPB_SecPerClus;                         /* Sectors per cluster. */
    uint16_t BPB_RsvdSecCnt;                        /* Number of reserved sectors . */
    uint8_t BPB_NumFATs;                            /* Number of FATs. */
    uint16_t BPB_RootEntCnt;                        /* Maximum number of root directory entries. */
    uint16_t BPB_TotSec;                            /* Total sector count. */
    uint16_t BPB_FATSz;                             /* Number of sector per FAT */
}fat_boot_sector_infor_t;

/* offset of file system. */
typedef struct
{
    uint8_t BootSec;                                /* Area bootsector. */
    uint8_t FAT1;                                   /* Area file allocate table 1. */
    uint8_t FAT2;                                   /* Area file allocate table 2. */
    uint8_t Root;                                   /* Area root directory. */
    uint8_t Data;                                   /* Area data. */
}fat_offset_file_FAT_t;

/* Struct stores byte information of entry in Root Directory. */
typedef struct
{
    uint8_t fileName[8];                            /* The short file name of directory, offset: 0x00 - 0x07. */
    uint8_t extension[3];                           /* The extention of file name, offset: 0x08 - 0x0A. */
    uint8_t attributes;                             /* The attribute of directory entry, offset: 0x0B. */
    uint16_t reserved;                              /* Reserved for Windows, offset: 0x0C. */
    uint16_t creationTime;                          /* Save creation time of directory (time): 0x0E - 0x0F. */
    uint16_t creationDate;                          /* Save creation time of directory (date): 0x10 - 0x11. */
    uint16_t lastAccessDate;                        /* Save the last access of dirctory (date): 0x12 - 0x13. */
    uint16_t ignoreInFAT12;                         /* Ignore in FAT12 */
    uint16_t lastWriteTime;                         /* Save the last modified of directory (time): 0x16 - 0x17. */
    uint16_t lastWriteDate;                         /* Save the last modified of directory (date): 0x18 - 0x19. */
    uint16_t firstLogicalCluster;                   /* The first cluster of  entry directory, offset: 0x1A - 0x1B. */
    uint32_t fileSize;                              /* The file size of directory, offset: 0x1C - 0x1F. */
    uint8_t entryNumbers;                           /* Save number entry in linked list. */
}fat_field_entry_t;

/* Node struct of entry. */
typedef struct node
{
    fat_field_entry_t data;                         /* Data contain all field of entry. */
    struct node *pNext;                             /* pNext pointer points to the next node. */
}fat_node_t;

/* Collection struct: list of root directory and subdirectory. */
typedef struct collection
{
    fat_node_t *pHead;                              /* pHead pointer contain 1 node head of root dirctory list  */
    fat_node_t *pTail;                              /* pTail pointer contain 1 node tail of root dirctory list */
    uint16_t lenght;                                /* Save length of root directory list. */
}fat_collection_root_t;

/* Struct stores byte information of data file. */
typedef struct
{
    uint8_t dataFile[NUMBER_OF_BYTE_PER_SECTOR];    /* Save data of file per one sector */
}fat_data_of_file_t;

/* Node struct of data file. */
typedef struct node_file
{
    fat_data_of_file_t data;                        /* Save data of 1 list file. */
    struct node_file *pNext;                        /* pNext pointer points to the next node_file. */
}fat_node_of_file_t;

/* Collection struct of data file. */
typedef struct collection_file
{
    fat_node_of_file_t *pHead;                      /* pHead pointer contain 1 node head of file list */
    fat_node_of_file_t *pTail;                      /* pHead pointer contain 1 node tail of file list */
    uint16_t lenght;                                /* Save length of file list. */
}fat_collection_file_t;

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* Add static API prototype in C file inside :
* Prototypes
******************************************************************************/

/* Init FAT. This funtion contain all information of disk. */
/* Paramater 1: File path. */
/* Paramater 2: Address of pointer. */
/* Return: result 1 is successful, 0 is faild */
uint8_t fatsInit(const uint8_t const *filePath, fat_boot_sector_infor_t **btSecInfor);

/* Read root directory. This funtion contain all information of area root directory. */
/* Paramater: Address of pointer. */
void readRootDirectory(fat_collection_root_t **rootList);

/* Read sub directory. This funtion contain all information of sub directory. */
/* Paramater 1: Address of pointer type fat_collection_root_t. */
/* Paramater 2: index in root directory list. */
void readSub(fat_collection_root_t **rootList, uint16_t index);

/* Read file. This funtion contain all data of file when read file. */
/* Paramater 1: Address of pointer type fat_collection_file_t. */
/* Paramater 2: index in root directory list or sub directory list. */
void readFile(fat_collection_file_t **fileList, uint16_t index);

/* Go to back. This funtion to check if first cluster equal 0 then go to back read root directory. */
/* Paramater: Address of pointer type fat_collection_file_t. */
/* Return sate: FUN_OK is funtion succesful, NOT_OK is funtion is faild. */
state goToBack(fat_collection_root_t **rootList);

/* Read sub directory or file. This funtion to check at index of list is sub director or file. */
/* Paramater: index in root directory list or sub directory list. */
/* Return state: READ_SUB is read sub directory, READ_FILE is read file, NO_READ_ANYTHING is no read anything */
state readSubOrFile(uint16_t index);

#endif