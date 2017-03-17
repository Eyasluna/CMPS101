//-----------------------------------------------------------------------------
// Implementation file for List ADT
//  Yibo Fu
//  CMPS 101
//  Integer List ADT is a bi-directional queue that has a cursor for List travsing.
//-----------------------------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
   int data;
   struct NodeObj* newnext;
   struct NodeObj* newprev;
} 
NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj
{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data)
{
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->newnext = NULL;
   N->newprev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN)
{
   if( pN!=NULL && *pN!=NULL )
   {
      free(*pN);
      *pN = NULL;
   }
}
// Constructor
// Createss a new empty List
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->length = 0;
   L->front = L->back = NULL;
   L->index = -1;
   L->cursor=NULL;
   return(L);
}
//Destructor
void freeList(List* pL)
{
   if(pL!=NULL && *pL!=NULL)
   {
	   while(length(*pL)!=0)
	   {
		   deleteFront(*pL);
	   }
	  free(*pL);
      *pL=NULL;
   }
}


// Access functions -----------------------------------------------------------
//length()
//Returns the number of elements in List
int length(List L)
{
   return L->length;
}
//index()
//If cursor is defined return the index
int index(List L)
{
   if(L->cursor==NULL)
   {
      return -1;
   }
   else
      return L->index;
}
//front()
//Returns front element
//Pre:elgnth()>0
int front(List L)
{
   if(L->length<1)
   {
      printf("List Error: calling front() on List length<1");
      exit(1);
   }
   return L->front->data;
}
//back()
//Returns back elemenet
//Pre:length()>0
int back(List L)
{
   if(L->length<1)
   {
      printf("List Error: calling back() on List length<1");
      exit(1);
   }
   return L->back->data;
}
//get()
//Returns cursor element
//Pre:length()>0, index()>=0
int get(List L)
{
   if(length(L)<0)
   {
      printf("List Error: calling get() on List length<1");
      exit(1);
   }
   else if(index(L)==-1||L->cursor==NULL)
   {
      printf("List Error:calling get() on List cursor index <0");
      exit(1);
   }
   return L->cursor->data;
}
//equals()
//Return 1 if both L have same element and length
//cursor is ignored in this function
int equals(List A, List B)
{
   
   int equal;
   equal=0;
   if(length(A)==length(B))
   {
      Node M = NULL;
      Node N = NULL;
      for(M=A->front, N=B->front; M!=NULL ; M=M->newnext, N=N->newnext)
      {
         if(M->data==N->data)
         {
            equal=1;
         }
         else
         {
            return 0;
         }
      }
      return equal;
   }
   else
      return 0;
}
// Manipulation procedures ----------------------------------------------------
//clea()
//Resets this List to its original empty state
void clear(List L)
{
	while(length(L)!=0)
	   {
		   deleteFront(L);
	   }
}
//moveFront()
//If List is non-emepty, places the cursor at front element, otherwise, do nothing
void moveFront(List L)
{
   if(L->length!=0)
   {
     L->cursor=L->front;
     L->index=0;
   }
}
//moveBack()
//place curosr at Back element if List is not empty
void moveBack(List L)
{
   if(L->length!=0)
   {
      L->cursor=L->back;
      L->index=length(L)-1;
   }
}
//movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
   if(L->cursor->newprev==NULL && L->cursor==L->front)
   {
      L->cursor=NULL;
      L->index=-1;
   }
   else
   {
      L->cursor=L->cursor->newprev;
      L->index--;
   }
}
//moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L)
{
   if(L->cursor->newnext==NULL && L->cursor==L->back)
   {
      L->cursor=NULL;
      L->index=-1;
   }
   else
   {
      L->cursor=L->cursor->newnext;
      L->index++;
   }
}
//prepend()
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data)
{
   if(L->length==0)
   {
      L->front=L->back=L->cursor=newNode(data);
      L->length++;
   }
   else
   {
      Node G=newNode(data);
      G->newnext=L->front;
      L->front->newprev=G;
      L->front=G;
      L->length++;
      L->index++;
   }
}
//append(int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data)
{
   if(L->length==0)
   {
      L->front=L->back=L->cursor=newNode(data);
      L->length++;
   }
   else
   {
      Node G = newNode(data);
      L->back->newnext=G;
      G->newprev=L->back;
      L->back=G;
      L->length++;
   }
}
//insertBefore(int data)
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data)
{
   if(L->length<=0)
   {
      printf("List Error:insertBefore() pre-condition violated, length<=0");
      exit(1);
   }
   else if(L->index<0)
   {
      printf("List Error:insertBefore() pre-condition violated, index<0");
      exit(1);
   }
   else if(L->cursor->newprev==NULL)
   {
      L->front= newNode(data);
      L->cursor->newprev=L->front;
      L->front->newnext=L->cursor;
      L->index++;
   }
   else
   {
      Node N=newNode(data);
      N->newnext=L->cursor;
      movePrev(L);
      N->newprev=L->cursor;
      L->cursor->newnext=N;
      moveNext(L);
      moveNext(L);
      L->cursor->newprev=N;
   }
   L->length++;
}
//insertAfter(int data)
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
   if(L->length<=0)
   {
      printf("List Error:insertBefore(int data) pre-condition violated, length()<=0");
      exit(1);
   }
   else if(L->cursor->newnext==NULL)
   {
      L->back=newNode(data);
      L->back->newprev=L->cursor;
      L->cursor->newnext=L->back;
   }
   else
   {
      Node N=newNode(data);
      N->newprev=L->cursor;
      moveNext(L);
      N->newnext=L->cursor;
      L->cursor->newprev=N;
      movePrev(L);
      movePrev(L);
      L->cursor->newnext=N;
      L->index++;
   }
   L->length++;
}
//deleteFront()
//Deletes the front element
//Pre:length()>0
void deleteFront(List L)
{
	Node N=NULL;
   if(L->length<1)
   {
      printf("List Error:deleteFront() pre-condition violated, length<1");
      exit(1);
   }
   else
   {
	   N=L->front;
      L->front=L->front->newnext;
      if(L->index==0)
      {
         L->cursor=NULL;
         L->index=-1;
      }
      else
         L->index--;
      L->length--;
   }
   freeNode(&N);
}
//deleteBack()
//Deletes the back element
//Pre:length()>0
void deleteBack(List L)
{
	Node N=NULL;
   if(L->length<1)
   {
      printf("List Error:deleteFront() pre-condition violated, length<1");
      exit(1);
   }
   else
   {
	   N=L->back;
      L->back=L->back->newprev;
      if(L->index==L->length-1)
      {
         L->cursor=NULL;
         L->index=-1;
      }
      L->length--;
   }
   freeNode(&N);
}
//delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L)
{
   if(length(L)<1)
   {
      printf("List Error:delete() pre-condition violated, length<1");
      exit(1);
   }
   else if(index(L)<1)
   {
      printf("List Error:delete() pre-condition violated, index()<1");
      exit(1);
   }
   else
   {
      if(index(L)==0)
      {
         deleteFront(L);
      }
      else if(index(L)==length(L)-1)
      {
         deleteBack(L);
      }
      else
      {
		 Node N=L->cursor;
         L->cursor->newprev->newnext=L->cursor->newnext;
         L->cursor->newnext->newprev=L->cursor->newprev;
         freeNode(&N);
		 L->cursor=NULL;
         L->index=-1;
         L->length--;
      }
   }
}
//Other methods------------
//printList()
//print out element in L to out File
void printList(FILE* out, List L)
{
   Node N=NULL;
   for(N=L->front; N!=NULL; N=N->newnext)
   {
      fprintf(out,"%d ", N->data);
   }
}
//copyList()
//Returns new List identical to the one at the argument except for cursor
List copyList(List L)
{
   List temp=newList();
   Node M=NULL;
   for(M=L->front; M!=NULL; M=M->newnext)
   {
      append(temp, M->data);
   }
   temp->cursor=NULL;
   temp->index=-1;
   return temp;
}
