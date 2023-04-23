/*
*******************************************************************************
* @file    manageLinkedList.c
* @author  Tran_Khanh_Dat
* @brief   This file is used to analyze data and perform required functions
*******************************************************************************/

#include "header.h"
#include <stdlib.h>
#include <stdio.h>


/*******************************************************************************
 * Code
 ******************************************************************************/

static Node array[MAX];

void initializeArray(uint8_t index)
{
    for (index = 0U; index < MAX; index++)
    {
        array[index].data = -1U;
        array[index].next = NULL;
    }
}
Node *initializeNode(uint32_t value)
{
    uint8_t index = 0U;
    Node *newNode;
    while (array[index].data != -1U)
    {
        index++;
    }
    newNode = &array[index];
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}
void addHead(Collection *linkedList, Node *node)
{
    if (linkedList->head == NULL)
    {
        linkedList->head = node;
    }
    else
    {
        node->next = linkedList->head;
        linkedList->head = node;
    }
}
void addTail(Collection *linkedList, Node *node)
{
    Node *nodeTemp;
    if (linkedList->head == NULL)
    {
        linkedList->head = node;
    }
    else
    {
        nodeTemp = linkedList->head;
        while (nodeTemp->next != NULL)
        {
            nodeTemp = nodeTemp->next;
        }
        nodeTemp->next = node;
    }
}
uint32_t enterNodeSize()
{
    uint32_t size;
    printf("Enter size of List: ");
    while (isValidUi32(&size) != STATUS_OK || 1 > size || size > MAX)
    {
        /* Enter the number of elements of the array. */
        fflush(stdin);
        printf("Wrong size of List\n");
        printf("Please re-enter the size of List\n");
        printf("Enter size of List: ");
    }
    return size;
}
uint32_t enterValue(uint8_t index)
{
    uint32_t value;
    printf("Node %hhu: ", index);
    while ((isValidUi32(&value) != STATUS_OK) || (1 > value) || (value > 100000))
    {
        /* Enter the number of elements of the array. */
        fflush(stdin);
        printf("Wrong value of Node\n");
        printf("Please re-enter the value of Node\n");
        printf("Node %hhu: ", index);
    }
    return value;
}
uint32_t enterPosition(uint8_t range)
{
    uint32_t position;
    printf("Enter position: ");
    while ((isValidUi32(&position) != STATUS_OK) || (position > range))
    {
        /* Enter the number of elements of the array. */
        fflush(stdin);
        printf("Wrong position\n");
        printf("Please re-enter the postion of List\n");
        printf("Enter position: ");
    }
    return position;
}
uint32_t enterKeyValue()
{
    uint32_t keyValue;
    printf("Enter key value: ");
    while ((isValidUi32(&keyValue) != STATUS_OK) || (1 > keyValue) || (keyValue > 100000))
    {
        /* Enter the number of elements of the array. */
        fflush(stdin); // Clear cache
        printf("Wrong value of Node\n");
        printf("Please re-enter the value of Node\n");
        printf("Enter key value: ");
    }
    return keyValue;
}
STATUS initializeLinkedList(Collection *linkedList)
{
    printf("---------------------------------------------INITIALIZE LINKED LIST----------------------------------------------\n\n");
    STATUS retVal = STATUS_OK;
    Node *newNode;
    uint8_t index = 0U;
    uint32_t value = 0U;
    if (linkedList->size != 0U)
    {
        retVal = STATUS_ERROR;
    }
    else
    {
        initializeArray(index);
        linkedList->size = enterNodeSize();
        for (index = 0U; index < linkedList->size; index++)
        {
            value = enterValue(index);
            newNode = initializeNode(value);
            addTail(linkedList, newNode);
        }
    }
    return retVal;
}
void insertNode(Collection *linkedList, Node *node, uint8_t position)
{
    Node *nodeTemp;
    uint8_t countIndex = 1;
    if (position == linkedList->size)
    {
        addTail(linkedList, node);
    }
    else if (position == 0U)
    {
        addHead(linkedList, node);
    }
    else
    {
        nodeTemp = linkedList->head;
        while (nodeTemp->next != NULL && countIndex != position)
        {
            nodeTemp = nodeTemp->next;
            countIndex++;
        }
        node->next = nodeTemp->next;
        nodeTemp->next = node;
    }
    linkedList->size++;
}
void addElement(Collection *linkedList)
{
    printf("---------------------------------------------ADD ELEMENT----------------------------------------------\n\n");
    uint8_t position;
    uint32_t value;
    Node *node;
    if (linkedList->size == 0U)
    {
        printf("Linked List doesn't exist\n");
    }
    else
    {
        position = enterPosition(linkedList->size);
        value = enterValue(position);
        node = initializeNode(value);
        insertNode(linkedList, node, position);
    }
    system("pause");
}
STATUS deleteLinkedList(Collection *linkedList)
{
    printf("---------------------------------------------DELETE LINKED LIST----------------------------------------------\n\n");
    STATUS retVal = STATUS_OK;
    uint8_t index;
    if (linkedList->size == 0U)
    {
        retVal = STATUS_ERROR;
    }
    else
    {
        for (index = 0; index < linkedList->size; index++)
        {
            array[index].data = -1U;
            array[index].next = NULL;
        }
        linkedList->head = NULL;
        linkedList->size = 0U;
        printf("Linked list has been removed\n");
    }
    return retVal;
}
void deleteNode(Collection *linkedList, uint8_t postion)
{
    Node *nodeCurrent;
    Node *nodePrevious;
    uint8_t countIndex = 0;
    nodePrevious = linkedList->head;
    nodeCurrent = nodePrevious->next;
    while (nodeCurrent->next != NULL && countIndex != postion)
    {
        nodePrevious = nodeCurrent;
        nodeCurrent = nodeCurrent->next;
        countIndex++;
    }
    nodeCurrent->data = -1U;
    nodePrevious->next = nodeCurrent->next;
    nodeCurrent->next = NULL;
    linkedList->size--;
}
void deleteElement(Collection *linkedList)
{
    printf("---------------------------------------------DELETE ELEMENT----------------------------------------------\n\n");
    uint8_t position;
    if (linkedList->size == 0U)
    {
        printf("Linked List doesn't exist\n");
    }
    else
    {
        position = enterPosition(linkedList->size - 1U);
        deleteNode(linkedList, position);
    }
    system("pause");
}
void searchList(Collection *linkedList, uint32_t keyValue)
{
    Node *nodeTemp;
    uint8_t indexTemp = 0U;
    uint8_t index = MAX;
    nodeTemp = linkedList->head;
    while (nodeTemp != NULL)
    {
        if (nodeTemp->data == keyValue)
        {
            index = indexTemp;
            printf("Number %u is in Node %hhu\n", keyValue, index);
            break;
        }
        nodeTemp = nodeTemp->next;
        indexTemp++;
    }
    if (index == MAX)
    {
        printf("Linked List doesn't contain the number %u\n", keyValue);
    }
}
void search(Collection *linkedList)
{
    printf("---------------------------------------------SEARCH----------------------------------------------\n\n");
    uint32_t keyValue;
    if (linkedList->size == 0U)
    {
        printf("List doesn't exist\n");
    }
    else
    {
        keyValue = enterKeyValue();
        searchList(linkedList, keyValue);
    }
    system("pause");
}
STATUS printList(Collection *linkedList)
{
    printf("---------------------------------------------PRINT LINKED LIST----------------------------------------------\n\n");
    STATUS retVal = STATUS_OK;
    Node *nodeTemp;
    if (linkedList->size == 0U)
    {
        retVal = STATUS_ERROR;
    }
    else
    {
        nodeTemp = linkedList->head;
        while (nodeTemp->next != NULL)
        {
            printf("%u\t", nodeTemp->data);
            nodeTemp = nodeTemp->next;
        }
        printf("%u", nodeTemp->data);
        printf("\n");
    }
    return retVal;
}
void swap(uint32_t *left, uint32_t *right)
{
    /* Use an intermediate memory variable to swap 2 values. */
    uint32_t temp = *left;
    *left = *right;
    *right = temp;
}
bool ascending(uint32_t left, uint32_t right)
{
    /* Returns true if the value on the left is greater than the value on the right. */
    return left > right;
}
bool descending(uint32_t left, uint32_t right)
{
    /* Returns true if the value on the left is less than the value on the right. */
    return left < right;
}
void selectSort(Collection *linkedList, bool compareFunction(uint32_t, uint32_t))
{
    uint8_t i, j;
    Node *nodeCurrent;
    Node *nodeNext;
    for (i = 0; i < linkedList->size - 1; i++)
    {
        nodeCurrent = linkedList->head;
        nodeNext = nodeCurrent->next;
        /* Get the elements behind and compare with the previous element. */
        for (j = i + 1; j < linkedList->size; j++)
        {
            /* Call ascending or descending to sort ascending or descending. */
            if (compareFunction(nodeCurrent->data, nodeNext->data))
            {
                swap(&nodeCurrent->data, &nodeNext->data);
            }
            nodeCurrent = nodeCurrent->next;
            nodeNext = nodeCurrent->next;
        }
    }
}
void ascendingSort(Collection *linkedList, bool compareFunction(uint32_t, uint32_t))
{
    printf("---------------------------------------------SORT LIST IN ASCENDING ORDER----------------------------------------------\n\n");
    if (linkedList->size == 0)
    {
        printf("List doesn't exist\n");
    }
    else
    {
        selectSort(linkedList, ascending);
        printf("|List is sorted ascending\n\n");
    }
    system("pause");
}
void descendingSort(Collection *linkedList, bool compareFunction(uint32_t, uint32_t))
{
    printf("---------------------------------------------SORT LIST IN DESCENDING ORDER----------------------------------------------\n\n");
    if (linkedList->size == 0)
    {
        printf("List doesn't exist\n");
    }
    else
    {
        selectSort(linkedList, descending);
        printf("List is sorted descending\n");
    }
    system("pause");
}