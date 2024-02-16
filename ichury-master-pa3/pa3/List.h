/****************************************************************************************
*  Graph.h 
*  Header file for the List ADT within List.c 
*  Isha Chury 
*  ichury
*  pa1/pa2/pa3 (used in all of these assignments)
*****************************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//INCLUDE STRUCT
//typedef struct List List; 
typedef struct ListObj* List;

List newList(void); 
void freeList(List* pL); 

int length(List L); 
int index(List L); 
int front(List L); 
int back(List L); 
int get(List L); 
bool equals(List A, List B); 

void clear(List L); 
void set(List L, int x); 
void moveFront(List L); 
void moveBack(List L); 
void movePrev(List L); 
void moveNext(List L); 

void prepend(List L, int x); 
void append(List L, int x); 
void insertBefore(List L, int x); 
void insertAfter(List L, int x); 

void deleteFront(List L); 
void deleteBack(List L); 
void delete(List L); 

void printList(FILE* out, List L); 
List copyList(List L); 


