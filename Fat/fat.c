/********************************************************************************
* @file    fat.c
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions prototypes for the FAT file
*          system
*******************************************************************************/

#include "fat.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/
#define BYTE_NUMBER_OF_ENTRY    (32U)

#define OFFSET_ATTRIBUTES       (0x0BU)
#define OFFSET_RESERVED         (0x02U)
#define OFFSET_OF_BOOT_SECTOR   (0x00U)
#define OFFSET_OF_END_ENTRY     (0x00U)

#define LONG_FILE_NAME          (0x0FU)
#define END_OF_FILE             (0XFFFU)

#define IS_FOLDER               (0x10U)
#define IS_FILE                 (0x00U)
#define IS_END_ENTRY            (0x00U)

/*******************************************************************************
* Variables
******************************************************************************/

static fat_boot_sector_infor_t g_bootSectorInfor;                  /* Declare static variable to store information of boot sector. */
static fat_offset_file_FAT_t g_offsetFileFAT;                      /* Declare static variable to store information of offset file FAT. */
static fat_field_entry_t g_fieldEntry;                             /* Declare static variable to store information field of entry. */
static fat_data_of_file_t g_dataOfFile;                            /* Declare static variable to store data of file. */

static fat_collection_root_t g_cltOfRoot;                          /* Declare static variable to store information of list root directory. */
static fat_collection_file_t g_cltOfFile;                          /* Declare static variable to store information of list file. */

static state s_checkAlreadyReadRoot = NOT_OK;                      /* Declare static variable to store information of state read root directory. */
static state s_checkAlreadySub = NOT_OK;                           /* Declare static variable to store information of state read sub directory. */

/*******************************************************************************
* Add static API prototype in C file inside :
* Prototypes
******************************************************************************/

/* Init root directory list. */
/* Paramater: 1 list type fat_collection_root_t. */
static void initCollectionOfRoot(fat_collection_root_t *list);

/* Create 1 node root directory list. */
/* Paramater: value type fat_field_entry_t. */
/* Return the address of the newly created node. */
static fat_node_t *createNodeOfRoot(fat_field_entry_t value);

/* Add the end 1 node of root directory list. */
/* Paramater 1: list type fat_collection_root_t. */
/* Paramater 2: value type fat_field_entry_t. */
static void addEndOfRoot(fat_collection_root_t *rootList, fat_field_entry_t value);

/* Init root file list. */
/* Paramater: 1 list type fat_collection_root_t. */
static void initCollectionOfFile(fat_collection_file_t *list);

/* Create 1 node file list. */
/* Paramater: value type fat_data_of_file_t. */
/* Return the address of the newly created node. */
static fat_node_of_file_t *createNodeOfFile(fat_data_of_file_t value);

/* Add the end 1 node of file list. */
/* Paramater 1: list type fat_collection_file_t. */
/* Paramater 2: value type fat_data_of_file_t. */
static void addEndOfFile(fat_collection_file_t *fileList, fat_data_of_file_t value);

/* Get 2 bytes from buffer. */
/* Paramater: buffer. */
/* Return value 2 bytes. */
static inline uint16_t get16(const uint8_t *buffer);

/* Get 4 bytes from bufer. */
/* Paramater: buffer. */
/* Return value 4 bytes. */
static inline uint32_t get32(const uint8_t *buffer);

/* The partitions of the file allocate table. */
/* Paramater: void */
static void offsetFile(void);

/* Information processing of entry field. */
/* Paramater: array buffer 32 element */
static void getInforFieldEntry(uint8_t *tempBuff);

/* Read value FAT at index */
/* Paramater: index */
/* Return value already read */
static uint16_t readFAT(uint16_t index);

/* Free list root directory already save. */
/* Paramater: list type fat_collection_root_t */
static void freeListOfRoot(fat_collection_root_t *list);

/* Free list file already save. */
/* Paramater: list type fat_collection_file_t */
static void freeListOfFile(fat_collection_file_t *list);

/* Get value first cluster at index of list type fat_collection_root_t */
/* Paramater 1: list type fat_collection_root_t */
/* Paramater 2: index user-input preferences */
/* Return value at field first cluster */
static uint16_t getFirstClus(fat_collection_root_t rootList, uint16_t index);

/* Get value atributes at index of list type fat_collection_root_t */
/* Paramater 1: list type fat_collection_root_t */
/* Paramater 2: index user-input preferences */
/* Return value at field atribute */
static uint16_t getAtributes(fat_collection_root_t rootList, uint16_t index);

/*******************************************************************************
* Code
******************************************************************************/

static void initCollectionOfRoot(fat_collection_root_t *list)
{
    list->pHead = NULL;
    list->pTail = NULL;
    list->lenght = 0;
}

static fat_node_t *createNodeOfRoot(fat_field_entry_t value)
{
    fat_node_t *temp = (fat_node_t*)malloc(sizeof(fat_node_t));
    temp->data = value;
    temp->pNext = NULL;
    return temp;
}

static void addEndOfRoot(fat_collection_root_t *rootList, fat_field_entry_t value)
{
    fat_node_t *temp = createNodeOfRoot(value);
    if(rootList->pHead == NULL)
    {
        rootList->pHead = rootList->pTail = temp;
        rootList->lenght += 1;
    }else
    {
        rootList->pTail->pNext = temp;
        rootList->pTail = temp;
        rootList->lenght += 1;
    }
}

static void initCollectionOfFile(fat_collection_file_t *list)
{
    list->pHead = NULL;
    list->pTail = NULL;
    list->lenght = 0U;
}

static fat_node_of_file_t *createNodeOfFile(fat_data_of_file_t value)
{
    fat_node_of_file_t *temp = (fat_node_of_file_t*)malloc(sizeof(fat_node_of_file_t));
    temp->data = value;
    temp->pNext = NULL;
    return temp;
}

static void addEndOfFile(fat_collection_file_t *fileList, fat_data_of_file_t value)
{
    fat_node_of_file_t *temp = createNodeOfFile(value);
    if(fileList->pHead == NULL)
    {
        fileList->pHead = fileList->pTail = temp;
        fileList->lenght += 1;
    }else
    {
        fileList->pTail->pNext = temp;
        fileList->pTail = temp;
        fileList->lenght += 1;
    }
}

static inline uint16_t get16(const uint8_t *buffer)
{
    return buffer[0] | (buffer[1] << 8);
}

static inline uint32_t get32(const uint8_t *buffer)
{
    return buffer[0] | (buffer[1] << 8) | (buffer[2] << 16);
}

uint8_t fatsInit(const uint8_t const *filePath, fat_boot_sector_infor_t **btSecInfor)
{
    uint8_t result = 1U;
    uint8_t tempBuffer[NUMBER_OF_BYTE_PER_SECTOR] = { 0 };

    if(kmc_init(filePath) == true)
    {
        kmc_read_sector(OFFSET_OF_BOOT_SECTOR, tempBuffer);
        g_bootSectorInfor.BPB_BytsPerSec = get16(tempBuffer + BPB_BYTS_PER_SEC);
        g_bootSectorInfor.BPB_SecPerClus = tempBuffer[BPB_SEC_PER_CLUS];
        g_bootSectorInfor.BPB_RsvdSecCnt = get16(tempBuffer + BPB_RSVD_SEC_CNT);
        g_bootSectorInfor.BPB_NumFATs = tempBuffer[BPB_NUM_FATS];
        g_bootSectorInfor.BPB_RootEntCnt = get16(tempBuffer + BPB_ROOT_ENT_CNT);
        g_bootSectorInfor.BPB_TotSec = get16(tempBuffer + BPB_TOT_SEC_16);
        g_bootSectorInfor.BPB_FATSz = get16(tempBuffer + BPB_FAT_SZ_16);
    }
    else
    {
        result = 0U;
    }
    *btSecInfor = &g_bootSectorInfor;

    return result;
}

static void offsetFile(void)
{
    g_offsetFileFAT.FAT1 = g_bootSectorInfor.BPB_RsvdSecCnt;
    g_offsetFileFAT.FAT2 = g_offsetFileFAT.FAT1 + g_bootSectorInfor.BPB_FATSz;
    g_offsetFileFAT.Root = g_offsetFileFAT.FAT2 + g_bootSectorInfor.BPB_FATSz;
    g_offsetFileFAT.Data = g_offsetFileFAT.Root + (g_bootSectorInfor.BPB_RootEntCnt * BYTE_NUMBER_OF_ENTRY / g_bootSectorInfor.BPB_BytsPerSec);
}

static void getInforFieldEntry(uint8_t *tempBuff)
{
    memcpy(g_fieldEntry.fileName, tempBuff, 8U);        /* File name is 8 bytes in field entry. */
    memcpy(g_fieldEntry.extension, tempBuff+8U, 3U);       /* Extension is 3 bytes in field entry and offset is 0x08U. */
    g_fieldEntry.attributes = tempBuff[ATTRIBUTES];
    g_fieldEntry.reserved = get16(tempBuff + RESERVED);
    g_fieldEntry.creationTime = get16(tempBuff + CREATION_TIME);
    g_fieldEntry.creationDate = get16(tempBuff + CREATION_DATE);
    g_fieldEntry.lastAccessDate = get16(tempBuff + LAST_ACCESS_DATE);
    g_fieldEntry.ignoreInFAT12 = get16(tempBuff + IGNORE_IN_FAT_12);
    g_fieldEntry.lastWriteTime = get16(tempBuff + LAST_WRITE_TIME);
    g_fieldEntry.lastWriteDate = get16(tempBuff + LAST_WRITE_DATE);
    g_fieldEntry.firstLogicalCluster = get16(tempBuff + FIRST_LOGICAL_CLUSTER);
    g_fieldEntry.fileSize = get32(tempBuff + FILE_SIZE);
    g_fieldEntry.entryNumbers = g_fieldEntry.entryNumbers + 1U;
}

void readRootDirectory(fat_collection_root_t **rootList)
{
    uint8_t buffer[NUMBER_OF_BYTE_PER_SECTOR] = { 0 };
    uint8_t tempBuff[BYTE_NUMBER_OF_ENTRY] = { 0 };
    uint16_t countBuff;                /* Count buffer. */
    uint16_t cntTmpBuff;               /* Count temp buffer. */
    uint8_t endEntryflag = 0U;         /* Set the end entry flag = 0U */
    uint8_t longFileNameflag = 0U;     /* Set long file name flag = 0U */

    offsetFile();
    initCollectionOfRoot(&g_cltOfRoot);
    g_fieldEntry.entryNumbers = 0U;

    do
    {
        kmc_read_sector(g_offsetFileFAT.Root, buffer);
        for (countBuff = 0U; countBuff < NUMBER_OF_BYTE_PER_SECTOR && endEntryflag == 0U; countBuff+=32U)
        {
            for (cntTmpBuff = 0U; cntTmpBuff < BYTE_NUMBER_OF_ENTRY; cntTmpBuff++)
            {
                tempBuff[cntTmpBuff] = buffer[countBuff + cntTmpBuff];
            }

            if(tempBuff[0] == 0x00U)
            {
                endEntryflag = 1U;
            }
            else
            {
                if(tempBuff[OFFSET_ATTRIBUTES] == IS_FOLDER || tempBuff[OFFSET_ATTRIBUTES] == IS_FILE)
                {
                    getInforFieldEntry(tempBuff);

                    /* Add the end of root directory list. */
                    addEndOfRoot(&g_cltOfRoot, g_fieldEntry);
                }
                else
                {
                    longFileNameflag == 1U;
                }
            }
        }

        if(tempBuff[OFFSET_OF_END_ENTRY] != IS_END_ENTRY)
        {
            g_offsetFileFAT.Root = g_offsetFileFAT.Root + 1U;
        }

    } while (tempBuff[OFFSET_OF_END_ENTRY] != IS_END_ENTRY);

    s_checkAlreadyReadRoot = ROOT_OK;
    *rootList = &g_cltOfRoot;
}

static uint16_t readFAT(uint16_t index)
{
    offsetFile();
    static uint8_t buffer[NUMBER_OF_BYTE_PER_SECTOR * 9U] = { 0 };
    uint16_t indexByte;
    uint16_t valueOfFATAtInx;
    static uint8_t flag = 0U;

    if (flag == 0U)
    {
        kmc_read_multi_sector(g_offsetFileFAT.FAT1, g_bootSectorInfor.BPB_FATSz, buffer);
        flag = 1U;
    }

    /* Index even. */
    if (index % 2U == 0U)
    {
        indexByte = (index * 1.5);
        valueOfFATAtInx = get16(buffer + indexByte) & 0x0FFFU;
    }
    /* Index odd. */
    else
    {
        indexByte = (index * 1.5);
        valueOfFATAtInx = (get16(buffer + indexByte) & 0xFFF0U) >> 4U;
    }

    return valueOfFATAtInx;
}

static void freeListOfRoot(fat_collection_root_t *list)
{
    fat_node_t *tmp;

    while (list->pHead != NULL)
    {
        tmp = list->pHead;
        list->pHead = list->pHead->pNext;
        free(tmp);
    }
}

static void freeListOfFile(fat_collection_file_t *list)
{
    fat_node_of_file_t *tmp;

    while (list->pHead != NULL)
    {
        tmp = list->pHead;
        list->pHead = list->pHead->pNext;
        free(tmp);
    }
}

void readSub(fat_collection_root_t **rootList, uint16_t index)
{
    if(s_checkAlreadyReadRoot == ROOT_OK)
    {
        uint8_t buffer[NUMBER_OF_BYTE_PER_SECTOR] = { 0 };
        uint8_t tempBuff[32] = { 0 };
        uint16_t countBuff;
        uint16_t cntTmpBuff;
        uint8_t endEntryflag = 0U;
        uint8_t longFileNameflag = 0U;
        uint8_t count;
        uint16_t offset;
        uint16_t readValueFAT;
        uint8_t endFlag = 0U;
        uint16_t firstClus;

        offsetFile();
        g_fieldEntry.entryNumbers = 0U;
        offset = getFirstClus(g_cltOfRoot, index) + g_offsetFileFAT.Data;
        readValueFAT = getFirstClus(g_cltOfRoot, index);

        freeListOfRoot(&g_cltOfRoot);
        do
        {
            kmc_read_sector(offset - OFFSET_RESERVED, buffer);
            for (countBuff = 0U; countBuff < NUMBER_OF_BYTE_PER_SECTOR && endEntryflag == 0U; countBuff+= BYTE_NUMBER_OF_ENTRY)
            {
                for (cntTmpBuff = 0U; cntTmpBuff < BYTE_NUMBER_OF_ENTRY; cntTmpBuff++)
                {
                    tempBuff[cntTmpBuff] = buffer[countBuff + cntTmpBuff];
                }

                if(tempBuff[OFFSET_OF_END_ENTRY] == IS_END_ENTRY)
                {
                    endEntryflag = 1U;
                }
                else
                {
                    if(tempBuff[OFFSET_ATTRIBUTES] == 0x10U || tempBuff[OFFSET_ATTRIBUTES] == 0x00U)
                    {
                        getInforFieldEntry(tempBuff);
                        addEndOfRoot(&g_cltOfRoot, g_fieldEntry);
                    }
                    else
                    {
                        longFileNameflag == 1U;
                    }
                }
            }

            if(readFAT(readValueFAT) != END_OF_FILE && endEntryflag == 0U)
            {
                offset = readFAT(readValueFAT) + g_offsetFileFAT.Data;
                readValueFAT = readFAT(readValueFAT);
            }
            else
            {
                endFlag = 1U;
            }

        } while (endFlag == 0U);
        s_checkAlreadySub = SUB_OK;
    }
    else
    {
        /* pass. */
    }
    *rootList = &g_cltOfRoot;
}

void readFile(fat_collection_file_t **fileList, uint16_t index)
{
    if(s_checkAlreadyReadRoot == ROOT_OK)
    {
        uint8_t buffer[NUMBER_OF_BYTE_PER_SECTOR] = { 0 };
        uint16_t offset;
        uint16_t count;
        uint16_t countData;
        uint16_t readValueFAT;
        uint8_t endFlag = 0U;

        count = 1U;
        offsetFile();
        initCollectionOfFile(&g_cltOfFile);

        offset = getFirstClus(g_cltOfRoot, index) + g_offsetFileFAT.Data;
        readValueFAT = getFirstClus(g_cltOfRoot, index);

        freeListOfFile(&g_cltOfFile);
        do
        {
            kmc_read_sector(offset - OFFSET_RESERVED, buffer);

            for (countData = 0U; countData < NUMBER_OF_BYTE_PER_SECTOR; countData++)
            {
                g_dataOfFile.dataFile[countData] = buffer[countData];
            }

            addEndOfFile(&g_cltOfFile, g_dataOfFile);

            if(readFAT(readValueFAT) != END_OF_FILE)
            {
                offset = readFAT(readValueFAT) + g_offsetFileFAT.Data;
                readValueFAT = readFAT(readValueFAT);
            }
            else
            {
                endFlag = 1U;
            }

        } while (endFlag == 0U);

    }
    else
    {
        /* pass. */
    }

    *fileList = &g_cltOfFile;
}

static uint16_t getFirstClus(fat_collection_root_t rootList, uint16_t index)
{
    uint16_t count = 1U;

    while(rootList.pHead->pNext != NULL && count != index)
    {
        /* Update pHead. */
        rootList.pHead = rootList.pHead->pNext;
        count++;
    }

    return rootList.pHead->data.firstLogicalCluster;
}

static uint16_t getAtributes(fat_collection_root_t rootList, uint16_t index)
{
    uint16_t count = 1U;

    while(rootList.pHead->pNext != NULL && count != index)
    {
        /* Update pHead. */
        rootList.pHead = rootList.pHead->pNext;
        count++;
    }

    return rootList.pHead->data.attributes;
}

state goToBack(fat_collection_root_t **rootList)
{
    state checkFuntion = FUN_OK;

    if(getFirstClus(g_cltOfRoot, 2U) == 0U && s_checkAlreadySub == SUB_OK)
    {
        /* back root. */
        readRootDirectory(rootList);
    }
    else
    {
        checkFuntion = NOT_OK;
    }

    return checkFuntion;
}

state readSubOrFile(uint16_t index)
{
    state whatRead = NOT_OK;

    if(getAtributes(g_cltOfRoot, index) == 0x10U)
    {
        whatRead = READ_SUB;
    }
    else if(getAtributes(g_cltOfRoot, index) == 0x00U)
    {
        whatRead = READ_FILE;
    }
    else
    {
        /* pass. */
    }

    return whatRead;
}