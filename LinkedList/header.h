/*
*******************************************************************************
* @file    header.h
* @author  Tran_Khanh_Dat
* @brief   This file contains all the functions prototypes
*******************************************************************************/

#ifndef __HEADER_H
#define __HEADER_H
#include <stdint.h>
#include <stdbool.h>


/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define MAX 100
typedef struct node
{
	uint32_t data;
	struct node *next;
} Node;
typedef struct
{
	Node *head;
	uint8_t size;
} Collection;
typedef enum
{
	STATUS_OK,
	STATUS_ERROR,
} STATUS;


/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Add static API prototype in C file inside:
* Prototypes
******************************************************************************/

/**
 * @brief Use to create initial empty values ​​for the Node array
 *
 * @param index
 * @return void
 */
void initArray(uint8_t index);

/**
 * @brief Use to check the value that Node contains
 *
 * @param value
 * @return STATUS
 */
STATUS isValidUi32(uint32_t *value);

/**
 * @brief Use to check if the characters entered in the menu are valid
 *
 * @param request
 * @return STATUS
 */
STATUS isValidChar(char *request);

/**
 * @brief Use to show menu
 *
 * @return void
 */
void menu();

/**
 * @brief Use to create a new node
 *
 * @return Node
 */
Node *initializeNode(uint32_t value);

/**
 * @brief Use to add node to head of linked list
 *
 * @param linkedList
 * @param node
 * @return void
 */
void addHead(Collection *linkedList, Node *node);

/**
 * @brief Use to add node at the tail of linked list
 * @param linkedList
 * @param node
 * @return void
 */
void addTail(Collection *linkedList, Node *node);

/**
 * @brief Use to enter the linked list size
 *
 * @return uint32_t
 */
uint32_t enterNodeSize();

/**
 * @brief Use to enter the value that the node contains
 * @param index
 * @return uint32_t
 */
uint32_t enterValue(uint8_t index);

/**
 * @brief Use to enter position
 *
 * @param range
 * @return uint32_t
 */
uint32_t enterPosition(uint8_t range);

/**
 * @brief Use to enter the number you want to search in the linked list
 *
 * @return uint32_t
 */
uint32_t enterKeyValue();

/**
 * @brief Use to initialize linked list
 *
 * @param linkedList
 * @return STATUS
 */
STATUS initializeLinkedList(Collection *linkedList);

/**
 * @brief Use to insert a new node
 *
 * @param list
 * @param node
 * @param postion
 * @return void
 */
void insertNode(Collection *linkedList, Node *node, uint8_t position);

/**
 * @brief Use to add element in linked list
 *
 * @param linkedList
 * @return void
 */
void addElement(Collection *linkedList);

/**
 * @brief Use to delete linked list
 *
 * @param linkedList
 * @return STATUS
 */
STATUS deleteLinkedList(Collection *linkedList);

/**
 * @brief Use to delete a node
 *
 * @param linkedList
 * @param postion
 * @return void
 */
void deleteNode(Collection *linkedList, uint8_t postion);

/**
 * @brief Use to delete a node in linked list
 *
 * @param linkedList
 * @return void
 */
void deleteElement(Collection *linkedList);

/**
 * @brief Use to find value contained in linked list
 *
 * @param linkedList
 * @param keyValue
 * @return void
 */
void searchList(Collection *linkedList, uint32_t keyValue);

/**
 * @brief Use to find value contained in linked list
 *
 * @param linkedList
 * @return void
 */
void search(Collection *linkedList);

/**
 * @brief Use to add new node as an head node of list
 *
 * @param linkedList
 * @return STATUS
 */
STATUS printList(Collection *linkedList);

void swap(uint32_t *left, uint32_t *right);

bool ascending(uint32_t left, uint32_t right);

bool descending(uint32_t left, uint32_t right);

void selectSort(Collection *linkedList, bool compareFunction(uint32_t, uint32_t));

void ascendingSort(Collection *linkedList, bool compareFunction(uint32_t, uint32_t));

void descendingSort(Collection *linkedList, bool compareFunction(uint32_t, uint32_t));

/**
 * @brief Use to make menu selections
 *
 * @return void
 */
STATUS actions();


#endif /* __HEADER_H */
