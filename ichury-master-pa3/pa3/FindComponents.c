/****************************************************************************************
*  FindPath.c
*  Client program that uses Graph.c to find strongly connected components   
*  Isha Chury 
*  ichury
*  pa3 
*****************************************************************************************/

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char * argv[]){ //general format is copied from example code 
	FILE *in; 
	FILE *out; 
	
	if( argc != 3 ){
      		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
   	}

   	// open files for reading and writing 
   	in = fopen(argv[1], "r");
      	if( in==NULL ){
      		printf("Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   	}

   	out = fopen(argv[2], "w");
   	if( out==NULL ){
      		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(1);
   	}

	//I recieved a really low-level pseudo code for approaching this file from Simon during OH 
	
	int n, u, v = -1; //input handling  
	fscanf(in, "%d", &n); //scan vertices 
	Graph G = newGraph(n); 

	//Ishika helped me create and debug a lot of the code here 	
	while(fscanf(in, "%d %d", &u, &v) != EOF) { //she helped me rewrite this code snippet (it would go in an infinite loop D:) 
		if (u != 0 && v != 0){ //code copied from FindPath
			//fscanf(in, "%d %d", &u, &v); 
			addArc(G, u, v);
			continue;
			//printGraph(out, G);
		}
		else{
			break; //used to break the infinite loop
		}
        }
	
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G); //it works!!!! 
	fprintf(out, "\n"); 

	Graph T = transpose(G); 
	List TT = newList(); 	
	for(int x = 1; x <= getOrder(G); x++){ //Ishika helped me understand this part and write the code 
		append(TT, x); //append input to list  
	} 
	
	DFS(G, TT); 
	DFS(T, TT); 
	
	int comp = 0; //number of components  
	for(int y = 1; y <= getOrder(G); y++){ //Sahil helped me write and debug this 
		if(getParent(T, y) == NIL){    //he helped me understand what we were trying to do over here 
			comp++; 	
		} 
	} 
	
	fprintf(out, "G contains %d strongly connected components:\n", comp);
	List *C = calloc(comp, sizeof(List)); //Mayhar helped me write this code and explained what it was doing  
       	for(int k = 0; k < comp; k++){
		C[k] = newList(); 
	}

	
	//for(int y = 1; y <= comp; y++){
        int t = comp; //Ishika and Mayhar helped me write and debug this code snippet 
	for(moveFront(TT); index(TT) != -1; moveNext(TT)){ 
		if(getParent(T, get(TT))== NIL){
                        t--;
			//append(C, get(TT)); 
                }
		append(C[t], get(TT)); 
	} 
	 
	//printList(out, C); 
	//fprintf(stdout,"\n"); 
	//}  
	
       	for(int i = 0; i < comp; i++){ //minor edits 
		fprintf(out, "Component %d: ", i+1);
		printList(out, C[i]); 
		//fprintf(out, "\n");
	} 	
	 
	for(int i = 0; i < comp; i++){
		freeList(&C[i]); 
	} 

	free(C); 
	freeGraph(&G);
       	freeGraph(&T); 
	freeList(&TT); 	
	fclose(in); 
	fclose(out); 
	return 0; 

	//run DFS 
	//run Transpose of DFS 
	//must be same list?


}  
