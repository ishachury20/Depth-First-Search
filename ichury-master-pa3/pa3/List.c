/****************************************************************************************
*  List.c 
*  Implementation of List ADT
*  Isha Chury 
*  ichury
*  pa1/pa2/pa3 (used within all of these assignments)
*****************************************************************************************/

#include "List.h" 
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>  

//struct for Node 
typedef struct NodeObj* Node;

//struct for NodeObj (contains data, prev, and next)
typedef struct NodeObj{
	int data; 
	struct NodeObj* prev; //a tutor helped me edit this struct  
	struct NodeObj* next; 	
} NodeObj;

//struct for ListObj (contains front, back, cursor, length, and index) 
typedef struct ListObj{
	Node front;
        Node back;
        Node cursor;
        int length;
        int index; 
} ListObj; 

//Constructors-Destructors------------------------------------------------------------------
//constructor and destructor for the node 
//creates a new node 
Node newNode(int data){  
   	Node N = malloc(sizeof(NodeObj));
   	assert( N!=NULL );
   	N->data = data;
   	N->next = NULL;
	N->prev = NULL; 
   	return(N);
}

//frees a node and sets it to null (contains nothing)
void freeNode(Node* pN){ //a tutor helped me understand and edit this  
	if( pN!=NULL && *pN!=NULL ){ //general format copied from the professor's queue example 
      		free(*pN);
      		*pN = NULL;
   	}
}

//constructor and destructor for the List 
//creates an empty list 
List newList(void){ 
	List L = malloc(sizeof(ListObj));
  	assert(L!=NULL);
	L->front = NULL; 
	L->back = NULL; 
      	L->cursor = NULL; 
	L->index = -1; //A tutor helped me figure out what index was supposed to be set to for the undefined case 
	L->length = 0; 	
   	return(L);
} 

//frees a list and sets it to null (contains nothing) 
void freeList(List* pL){ //general format copied from the professor's queue example 
	if( pL!=NULL && *pL!=NULL ){
		//List pL = *pL 
      		while(length(*pL)>0){ //Bhaswati helped me figure this out 
			deleteFront(*pL); 
		} 
      		free(*pL); 
		*pL = NULL;
   	}
} 

//Manipulation Proecedures------------------------------------------------------------------
//clears an existing List and sets the cursor to undefined state 

void clear(List L){
	//clear list by deleting last element (via len) 	 
	while(L->length > 0){ //Bhaswati helped me figure out this loop  
		deleteBack(L);  
	} 
	//free(L); //double-check 
	L->front = NULL; //Bhaswati helped me understand to set this to the undefined state 
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1; 
        L->length = 0;
	return; 	
} 

//helper function--checks if the list is empty (returns bool value) 
//bool isEmpty(List L){
//   	if(L==NULL){ //general format copied from the professor's example queue code 
//      		printf("List Error: calling isEmpty() on NULL List reference\n");
//      		exit(EXIT_FAILURE);
//   	}
//   	return(L->length==0);
//} 

//overwrites the cursor's data with x 
//pre-condition: length()>0, index()>=0
//professor helped explain that the index and cursor are co-dependent 
void set(List L, int x){
	if(L==NULL){
		//general error message copied from professor's example code 
		printf("List Error: calling set() on NULL List reference\n");  
		exit(EXIT_FAILURE); 
	} 
	if(length(L)>0 && index(L)>=0){
		L->cursor->data = x;    	
	} 
	else{
		printf("List Error: calling set() on empty list reference\n"); 
		exit(EXIT_FAILURE); 
	} 
	return; 
} 

//sets the cursor to the front element of the list 
//pre-condition: L is not NULL 
void moveFront(List L){
	if(L==NULL){
		printf("List Error: calling moveFront() on NULL List reference\n"); 
		exit(EXIT_FAILURE); 
	} 
	if(length(L)>0){ //double check these conditions 
		L->cursor = L->front; 
		L->index = 0; 
	} 
	return; 
} 

//sets the cursor to the back element of the list 
//pre-condition: L is not NULL 
void moveBack(List L){ 
	if(L==NULL){
        	printf("List Error: calling moveBack() on NULL List reference\n");
                exit(EXIT_FAILURE);
	}
	if(length(L)>0){ //use isEmpty instead 
		L->cursor = L->back; 
		L->index = length(L)-1; 
	} 	
	return; 
} 
//sets the cursor towards the front of the list 
//pre-condition: L is not NULL 
void movePrev(List L){
	if(L==NULL){
		printf("List Error: calling movePrev() on NULL List reference\n");
                exit(EXIT_FAILURE);
	} 
	if(L->cursor >= 0 && L->cursor != L->front){
		L->cursor = L->cursor->prev; 
	       	L->index--; 	
	} 
	else if(L->cursor >= 0 && L->cursor == L->front){
		L->cursor = NULL; //undefined state  
		L->index = -1; 
	} 
	return; 
} 

//sets the cursors towards the back of the list  
//pre-condition: L is not NULL
void moveNext(List L){
	if(L==NULL){
		printf("List Error: calling moveNext() on NULL List reference\n");
                exit(EXIT_FAILURE);
	} 
	
	if(L->cursor >= 0 && (L->cursor != L->back)){
                L->cursor = L->cursor->next; 
		L->index++; 
        }
	else if(L->cursor >= 0 && (L->cursor == L->back)){
		L->cursor = NULL; 
		L->index = -1; 
	} 
	return; 
} 

//prepends an element in the list 
//pre-condition: if L is not empty, insert before the front element 
void prepend(List L, int x){
	if(L==NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
                exit(EXIT_FAILURE);
	} 
	Node N = newNode(x); 
	if(L->front == NULL){
		L->front = L->back = N; 
		//what about the cursor? 
	} 
	else{
		L->front->prev = N; 
		N->next = L->front; 
		L->front = N; 
		//L->index++; 
	} 
	if(L->index != -1){
		L->index++; 
	} 
	L->length++; 
       	return; 	
} 

//appends an element in the list 
//pre-condition: L is not NULL  
void append(List L, int x){ //Sahil helped me figure out this function  
	//Node N = newNode(x);
	if(L==NULL){
		printf("List Error: calling append() on NULL List reference\n");
                exit(EXIT_FAILURE);
	} 
	Node N = newNode(x);
	if(L->back==NULL){
		L->back = L->front = N;	
		//L->cursor = L->back; 
	}
	else{
		L->back->next = N;  
		N->prev = L->back; 
		L->back = N; 
		//N->next = NULL; 
	} 
	L->length++; 
	//L->index++; 
	return; 	
} 

//inserts a new element before the cursor
//pre-condition: L is not NULL, length()>0, index()>=0  
void insertBefore(List L, int x){
	//Node N = newNode(x);
	if(L==NULL){ 
		printf("List Error: calling insertBefore() on NULL List reference\n");
                exit(EXIT_FAILURE);
	} 	
	if(length(L)<=0 || index(L)<0){
		printf("List Error: calling insertBefore() on undefined cursor reference\n");
		exit(EXIT_FAILURE); 
	} 
	if(L->cursor == L->front){
                prepend(L, x);
                //L->index++;
		return; 
        } 
	else{ 
		Node N = newNode(x);
		//L->cursor->prev = N; 	
		//N->next = L->cursor; 
		N->prev = L->cursor->prev; 
		N->next = L->cursor; 

		//L->cursor->prev = N;
		L->cursor->prev->next = N; //Sheel helped me understand order was important to this block of code 
                                           //he helped me order my code for this function and the next
		L->cursor->prev = N;

		L->length++; 
		L->index++; 
		//what about the index? 
	} 
	return; 
} 

//inserts a new element after the cursor
//pre-condition: L is not NULL, length()>0, index()>=0
void insertAfter(List L, int x){
	//Node N = newNode(x);
	if(L == NULL){
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE); 
	} 
	if(L->cursor == L->back){
                append(L, x);
		return; 

                //no need to increment len, append does it for us :D
        }
	if(length(L)<=0 || index(L)<0){
		printf("List Error: calling insertAfter() on undefined cursor reference\n");
                exit(EXIT_FAILURE);
	} 
	else{ //length(L)>0 && index(L)>=0){ //index + len is defined
                Node N = newNode(x);
		//L->cursor->next = N; 
                
		//N->prev = L->cursor;  
                N->next = L->cursor->next; //Sheel helped me understand order was important to this block of code 
		N->prev = L->cursor;       //he helped me order my code for this function :D 

		L->cursor->next->prev = N;  
                L->cursor->next = N;

		L->length++; 
		L->index++; 	
	}
	return; 
}	

//deletes the front element of the list 
//pre-condition: length()>0
void deleteFront(List L){
	if(L==NULL){ //Simon helped me edit this function in OH 
		printf("List Error: calling deleteFront() on a NULL List reference\n");
                exit(EXIT_FAILURE);
	}
	//Node N = L->front; 
	Node N = NULL; 
	if(L->cursor == L->front){
		L->cursor = NULL; 
		L->index = -1; 
	} 
	N = L->front;
	if(length(L)>1){ 
      		L->front = L->front->next; 
		L->front->prev = NULL; //Amaan helped me debug deleteFront and deleteBack 
                                      //he fixed my valgrind error by adding this line of code 
   	}else{ 
      		L->front = L->back = NULL; 
   	}

	if(L->index != -1){
		L->index--; 
	} 
   	L->length--;
   	freeNode(&N);


	/*
		L->front->prev = NULL; 
	       	L->front = L->front->next; 
		//L->front->prev = NULL; 
		freeNode(&N);
		if(L->index == 0){
			L->index = -1; 
		} 
		else{ //index not at back 
			L->index--; 	
		} 
		L->length--; 	
	} */ 
	return; 
} 

//deletes the back element of the list
//pre-condition: length()>0
void deleteBack(List L){
	if(L==NULL){ 
		printf("List Error: calling deleteBack() on a NULL List reference\n");
                exit(EXIT_FAILURE);
	} 
	//I used the same format the previous function
        //Node N = NULL;
        if(L->cursor == L->back){
                L->cursor = NULL;
                L->index = -1;
        }
        Node N = L->back;	
	if(length(L)>1){
                L->back = L->back->prev;
		L->back->next = NULL; //Amaan helped me debug deleteFront and deleteBack 
				      //he fixed my valgrind error by adding this line of code 
        }else{
                L->front = L->back = NULL;
        }
        L->length--;
        freeNode(&N);
	N = NULL;	
		
		//L->back->next = NULL;
		//L->back = L->back->prev;
		//L->back->next = NULL;
		/*freeNode(&N); 
		if(L->index == 0){ 
			L->index = -1; 	
		} 
		else{ 
			L->index--; 
		} 
		L->length--; 
	}*/  
	return;
} 
//deletes the cursor element 
//pre-condition: L is not NULL, cursor is defined 
void delete(List L){
	if(L==NULL){
		printf("List Error: calling delete() on a NULL List reference\n");
                exit(EXIT_FAILURE);
	} 
	if(length(L)<=0 || L->cursor == NULL){
		printf("List Error: calling deleteFront() on an undefined cursor reference\n");
                exit(EXIT_FAILURE);
	} 
	if(L->cursor == L->front){
		deleteFront(L); 
		L->cursor = NULL; 
		L->index = -1; 
		return; 
	} 
	if(L->cursor == L->back){ //Sidharth helped me understand and write this function 
		deleteBack(L);    //he helped me understand the cases and what to write for each case 
		L->cursor = NULL;
		L->index = -1;
		return; 
	} 
	else{
		Node N = L->cursor; 
		L->cursor->prev->next = L->cursor->next;
        	L->cursor->next->prev = L->cursor->prev;
		freeNode(&N); 
		L->length--; 
		L->index = -1; 
		L->cursor = NULL;
	       	return; 	
	} 
	//L->cursor = NULL; 
        //L->index = -1;
	return; 
} 

//Access Functions------------------------------------------------------------------
//returns the number of elements in L.
////pre-condition: L is not NULL
int length(List L){
	if(L==NULL){
      		printf("List Error: calling length() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	return(L->length);
}

//returns the index of cursor element
//pre-condition: L is not NULL
int index(List L){
	if(L==NULL){
		printf("List Error: calling index() on NULL List reference\n");
                exit(EXIT_FAILURE); 
	}
	if(length(L)<=0){
	       	return -1; 
	} 
	return(L->index);   	
} 

//returns the front element of the list 
//pre-condition: L is not NULL, length()>0
int front(List L){
	if(L==NULL){
                printf("List Error: calling front() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
	if(length(L) > 0){
		return(L->front->data);	
	}
	else{
		printf("List Error: calling front() on empty List reference\n");
                exit(EXIT_FAILURE); 
	} 
} 

//returns the back element of the list
////pre-condition: L is not NULL, length()>0
int back(List L){
	if(L==NULL){
                printf("List Error: calling back() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
	if(length(L)>0){
		return(L->back->data); 
	} 
	else{
		printf("List Error: calling back() on empty List reference\n");
                exit(EXIT_FAILURE);
	} 
} 

//returns the cursor element of the list
////pre-condition: L is not NULL, length()>0, index()>=0
int get(List L){
	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
                exit(EXIT_FAILURE);
	} 
	if(L->cursor==NULL){
		printf("List Error: calling get() on undefined cursor reference\n");
                exit(EXIT_FAILURE);
	}  
	if(length(L)<=0){ // || index(L)<0){
		printf("List Error: calling get() on empty List reference\n");
                exit(EXIT_FAILURE);
	} 
	return(L->cursor->data);
} 

//returns true if list A and list B are in the same state
bool equals(List A, List B){
	if( A==NULL || B==NULL ){
      		printf("List Error: calling equals() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
	//general format of the code is from the professor's queue example 
   	bool eq;
   	Node N, M;

   	eq = ( A->length == B->length );
   	N = A->front;
   	M = B->front;
   	while( eq && N!=NULL){
      		eq = ( N->data==M->data );
     	 	N = N->next;
     		M = M->next;
   	}
   	return eq;
} 	

// Other Functions ------------------------------------------------------------

void printList(FILE* out, List L){
   	Node N = NULL;
	//general format of the code is from the professor's queue example 
   	if(L==NULL){
      		fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}

   	for(N = L->front; N != NULL; N = N->next){
      		fprintf(out, "%d", N->data);
		fprintf(out, " "); 
   	}
	fprintf(out, "\n");
}

List copyList(List L){ //Amman helped me write this code (edited and debugged it) 
    	List C = newList();
    	if (length(L) > 0){
        	Node N = L->front;
        	while (N != NULL){
            		append(C, N->data);
            		N = N->next;
        	}
    	}
    	C->cursor = NULL;
    	C->index = -1;
    	return C;
} 
