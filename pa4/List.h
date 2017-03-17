//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//  Yibo Fu
//  class:CMPS 101
//  Integer List ADT is a bi-directional queue that has a cursor for List
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------

void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);


// Other Functions ------------------------------------------------------------

void printList(FILE* out, List L);
List copyList(List L);

#endif