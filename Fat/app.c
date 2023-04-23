/********************************************************************************
* @file    app.c
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions for implementing with the FAT file system
*******************************************************************************/

#include "app.h"

/*******************************************************************************
* Add macros, enumeration types, structure types, inside:
* Definitions
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/

uint8_t filePath[] = { 0 };                         /* Declare array to store file path. */
fat_boot_sector_infor_t *g_bootInfor;               /* Declare global variable to store address of boot sector fat floor. */
fat_collection_root_t *g_rootList;                  /* Declare global variable to store address of root list fat floor. */
fat_collection_file_t *g_fileList;                  /* Declare global variable to store address of file list fat floor. */
app_date_modified_t g_dateModified;                 /* Declare global variable to store date modified of folder and file . */

/*******************************************************************************
* Add static API prototype in C file inside :
* Prototypes
******************************************************************************/

/*******************************************************************************
* Code
******************************************************************************/

uint8_t informatiomDisk()
{
    uint8_t result = 1U;

    rewind(stdin);
    printf("<! Please put your file path: ");
    scanf("%s", filePath);

    if(fatsInit(filePath, &g_bootInfor) == 1)
    {
        printf("\n---------------> INFORMATION DISK <---------------\n");
        printf("- Byte per sector \t: %d\n",    g_bootInfor->BPB_BytsPerSec);
        printf("- Sector per cluster \t: %d\n", g_bootInfor->BPB_SecPerClus);
        printf("- Reserved of count \t: %d\n",  g_bootInfor->BPB_RsvdSecCnt);
        printf("- Number FAT \t\t: %d\n",       g_bootInfor->BPB_NumFATs);
        printf("- Root entry count \t: %d\n",   g_bootInfor->BPB_RootEntCnt);
        printf("- Total sector \t\t: %d\n",     g_bootInfor->BPB_TotSec);
        printf("- Sector per FAT \t: %d\n",     g_bootInfor->BPB_FATSz);
        readRootDirectory(&g_rootList);
        printRootList(g_rootList);
    }
    else
    {
        result = 0U;
        printf("File path is invailid!");
        exit(1);
    }

    return result;
}

void informationProccessRoot(fat_collection_root_t *listOfRoot)
{
    fat_node_t *pNodeTemp = NULL;

    for (pNodeTemp = listOfRoot->pHead; pNodeTemp != NULL; pNodeTemp = pNodeTemp->pNext)
    {
        printf("|%d \t\t\t", pNodeTemp->data.entryNumbers);
        printf("|%.8s \t", pNodeTemp->data.fileName);
        if(pNodeTemp->data.attributes == 0x10U)
        {
            printf("|FOLDER \t");
        }
        else
        {
            printf("|%.3s DOCUMENT\t", pNodeTemp->data.extension);
        }
        g_dateModified.day = (pNodeTemp->data.lastWriteDate & 0x001FU);
        printf("|%.2d/", g_dateModified.day);
        g_dateModified.month = (pNodeTemp->data.lastWriteDate & 0x01E0U) >> 5U;
        printf("%.2d/", g_dateModified.month);
        g_dateModified.year = ((pNodeTemp->data.lastWriteDate & 0xFF00U) >> 9U) + 1980U;
        printf("%d ", g_dateModified.year);
        g_dateModified.hour = (pNodeTemp->data.lastWriteTime & 0xF800) >> 11U;
        printf("%.2d:",g_dateModified.hour);
        g_dateModified.minute = (pNodeTemp->data.lastWriteTime & 0x07E0) >> 5U;
        printf("%.2d \t",g_dateModified.minute);
        if(pNodeTemp->data.fileSize > 1024U)
        {
            pNodeTemp->data.fileSize = pNodeTemp->data.fileSize / 1024U;
            printf("|%d KB\t\t|", pNodeTemp->data.fileSize);
        }
        else
        {
            printf("|%d KB\t\t|", pNodeTemp->data.fileSize);
        }
        printf("\n");
    }
}

void printRootList(fat_collection_root_t *listOfRoot)
{
    if(listOfRoot->pHead == NULL)
    {
        printf("List is empty!\n");
    }
    else
    {
        printf("\n---------------------------------------> ROOT DIRECTORY <---------------------------------------\n");
        printf("|<!> OPPTION:\t\t|<!> NAME\t|<!> TYPE\t|<!> DATE MODIFIED\t|<!> SIZE\t|\n");
        informationProccessRoot(listOfRoot);
    }
}

void informationProccessSub(fat_collection_root_t *listOfRoot)
{
    uint8_t count = 0U;
    fat_node_t *pNodeTemp = NULL;

    for (pNodeTemp = listOfRoot->pHead; pNodeTemp != NULL; pNodeTemp = pNodeTemp->pNext)
    {
        if(count > 1U)
        {
            printf("|%d \t\t\t", pNodeTemp->data.entryNumbers);
            printf("|%.8s \t", pNodeTemp->data.fileName);

            if(pNodeTemp->data.attributes == 0x10U)
            {
                printf("|FOLDER \t");
            }
            else
            {
                printf("|%.3s DOCUMENT\t", pNodeTemp->data.extension);
            }

            g_dateModified.day = (pNodeTemp->data.lastWriteDate & 0x001FU);
            printf("|%.2d/", g_dateModified.day);

            g_dateModified.month = (pNodeTemp->data.lastWriteDate & 0x01E0U) >> 5U;
            printf("%.2d/", g_dateModified.month);

            g_dateModified.year = ((pNodeTemp->data.lastWriteDate & 0xFF00U) >> 9U) + 1980U;
            printf("%d ", g_dateModified.year);

            g_dateModified.hour = (pNodeTemp->data.lastWriteTime & 0xF800) >> 11U;
            printf("%.2d:",g_dateModified.hour);

            g_dateModified.minute = (pNodeTemp->data.lastWriteTime & 0x07E0) >> 5U;
            printf("%.2d \t",g_dateModified.minute);

            if(pNodeTemp->data.fileSize > 1024U)
            {
                pNodeTemp->data.fileSize = pNodeTemp->data.fileSize / 1024U;
                printf("|%d KB\t\t|", pNodeTemp->data.fileSize);
            }
            else
            {
                printf("|%d KB\t\t|", pNodeTemp->data.fileSize);
            }
            printf("\n");

        }
        else
        {
            count++;
        }
    }
}

void printSubList(fat_collection_root_t *listOfSub)
{
    uint16_t count = 0U;
    uint32_t tempSize = 0U;
    fat_node_t *pNodeTemp = NULL;
    if(listOfSub->pHead == NULL)
    {
        printf("List is empty!\n");
    }
    else
    {
        printf("\n----------------------------------------> SUB DIRECTORY <----------------------------------------\n");
        printf("|<!> OPPTION:\t\t|<!> NAME\t|<!> TYPE\t|<!> DATE MODIFIED\t|<!> SIZE\t|\n");
        printf("|1 (Refersh folder)\t|\t\t|\t\t|\t\t\t|\t\t|\n");
        printf("|2 (Back)\t\t|\t\t|\t\t|\t\t\t|\t\t|\n");
        informationProccessSub(g_rootList);
    }
}

void printFileList(fat_collection_file_t *listOfFile)
{
    printf("\n");
    uint8_t count;
    fat_node_of_file_t *pNodeTemp = NULL;

    if(listOfFile->pHead == NULL)
    {
        printf("List is empty!\n");
    }
    else
    {
        for (pNodeTemp = listOfFile->pHead; pNodeTemp != NULL; pNodeTemp = pNodeTemp->pNext)
        {
            printf("%s", pNodeTemp->data.dataFile);
        }
    }

    printf("\n");
}

void opption()
{
    int16_t choice = -1;
    uint8_t alreadyReadSubFlag = 0U;

    while (choice != 0U)
    {
        printf("0 (Exit program)\n");
        printf("Enter your choose: ");
        choice = checkScanChoice(g_rootList);
        if(choice > 0)
        {

            if(readSubOrFile(choice) == READ_SUB)
            {
                if(choice == 2U && goToBack(&g_rootList) == FUN_OK)
                {
                    printRootList(g_rootList);
                    alreadyReadSubFlag = 0U;
                }
                else
                {
                    readSub(&g_rootList, choice);
                    printSubList(g_rootList);
                    alreadyReadSubFlag = 1U;
                }
            }
            else if (readSubOrFile(choice) == READ_FILE)
            {
                readFile(&g_fileList, choice);
                printf("\n---------------> START FILE <---------------\n");
                printFileList(g_fileList);
                printf("\n---------------> END FILE <---------------\n");

                if(alreadyReadSubFlag == 1U)
                {
                    printSubList(g_rootList);
                }
                else
                {
                    printRootList(g_rootList);
                }

            }
        }

        else
        {
            kmc_deinit();
            printf("Exit Program!");
        }
    }
}

int16_t checkScanChoice(fat_collection_root_t *g_rootList)
{
    uint8_t flag = 0U;                          /* Declare flag to check value scan is vailid. */
    int16_t choice;

    while (flag == 0U)
    {
        if(((scanf("%hu", &choice)) == 0 && getchar() != '\n'))
        {
            printf("Value invailid!\nPlease enter again: ");
            clearSdtin();
        }
        else if((choice < 0) || (choice > g_rootList->pTail->data.entryNumbers))
        {
            printf("Value invailid!\nPlease enter again: ");
            clearSdtin();
        }
        else
        {
            /* Value is vailid. */
            flag = 1U;
        }
    }

    return choice;
}

void clearSdtin(void)
{
    while(getchar() != '\n')
    {}
}