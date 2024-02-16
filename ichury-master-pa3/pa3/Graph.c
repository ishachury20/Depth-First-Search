/****************************************************************************************
*  Graph.c
*  Implementation of Graph ADT
*  Isha Chury 
*  ichury
*  pa3 
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h> 
#include "Graph.h" 

typedef struct GraphObj{
	List* neighbors; 
	int* color; 
	int* parent; 
	int* discover;
       	int* finish; 	
	int order; 
	int size; 
} GraphObj; 

Graph newGraph(int n){
    	Graph G = malloc(sizeof(GraphObj));
    	G->neighbors = calloc(n + 1, sizeof(List));
    	G->color = calloc(n + 1, sizeof(int));
    	G->parent = calloc(n + 1, sizeof(int));
    	G->discover = calloc(n + 1, sizeof(int));
    	G->finish = calloc(n + 1, sizeof(int));

    	G->order = n;
    	G->size = 0;
    	for (int i = 1; i <= n; i++){
        	G->neighbors[i] = newList();
        	G->color[i] = WHITE;
        	G->parent[i] = NIL;
        	G->discover[i] = UNDEF;
        	G->finish[i] = UNDEF;
    	}
	return G;
}

void freeGraph(Graph* pG){
	for(int i=1; i < (getOrder(*pG))+1; i++){
		freeList(&(*pG)->neighbors[i]);
	}
	//free((*pG)->order);
	//(*pG)->order = NULL;

	free((*pG)->discover);
	free((*pG)->finish); 
	//(*pG)->distance = NULL;
	free((*pG)->color);
	//(*pG)->color = NULL;
	//(*pG)->neighbors = NULL;
	free((*pG)->parent);
	//(*pG)->parent = NULL;
	free((*pG)->neighbors);


	free(*pG);
	*pG = NULL;
}

int getOrder(Graph G){
	if(G == NULL){
                exit(EXIT_FAILURE);
        }
	//if(G->order < 0){
	//	exit(EXIT_FAILURE);
	//}
	return G->order;
}

int getSize(Graph G){
	if(G == NULL){
		exit(EXIT_FAILURE);
	}
	//if(G->size < 0){
	//	exit(EXIT_FAILURE);
	//}
	return G->size;
}

int getParent(Graph G, int u){
	if(G == NULL){
                exit(EXIT_FAILURE);
	}
	if(!(1 <= u && u <= getOrder(G))){
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}

int getDiscover(Graph G, int u){
    	if (G == NULL){
        	exit(1);
    	}
    	if (!(1 <= u && u <= getOrder(G))){
        	exit(1);
  	}
    	return G->discover[u];
}

int getFinish(Graph G, int u){
        if (G == NULL){
                exit(1);
        }
        if (!(1 <= u && u <= getOrder(G))){
                exit(1);
        }
	return G->finish[u]; 
} 

void addEdge(Graph G, int u, int v){
	if(G == NULL){
		exit(EXIT_FAILURE); 
		return; 
	}
       	if(!(1 <= u && u <= getOrder(G)) || (!(1 <= v && v <= getOrder(G)))){
		exit(EXIT_FAILURE);
		return;
	}
	
	addArc(G, u, v); 
	addArc(G, v, u); 	
	G->size--;
  
} 

void addArc(Graph G, int u, int v){
	if(G == NULL){
        	exit(EXIT_FAILURE);
                return;
        }
	if(!(1 <= u && u <= getOrder(G))){
                exit(EXIT_FAILURE);
                return;
	} 

	//insertion sort
	if(length(G->neighbors[u]) == 0){
		append(G->neighbors[u], v); 
	} 
	else{
		moveBack(G->neighbors[u]); //sort the list of u
        	int y = get(G->neighbors[u]); 
		while(index(G->neighbors[u]) != -1 && y > v){  //???  
                	movePrev(G->neighbors[u]);
			if(index(G->neighbors[u]) != -1){
				y = get(G->neighbors[u]); 
			} 
		} 	 
		if(y == v){
			return; 
		} 

		if(index(G->neighbors[u]) == -1) {   
                	prepend(G->neighbors[u], v); 
        	}
		else{
			insertAfter(G->neighbors[u], v); 
		} 
	} 
	//where does the while loop close?  
       	G->size++;  
} 

void visit(Graph G, List S, int u, int *time){
	//Sarah helped me write and debug this function 	
	G->discover[u] = ++(*time);
    	G->color[u] = GRAY;
    	moveFront(G->neighbors[u]);
    	while (index(G->neighbors[u]) >= 0){
        	int y = get(G->neighbors[u]);
        	if (G->color[y] == WHITE){
            		G->parent[y] = u;
            		visit(G, S, y, time);
        	}
        	moveNext(G->neighbors[u]);
    	}
    	G->color[u] = BLACK;
    	G->finish[u] = ++*time;
    	prepend(S, u);	
} 


void DFS(Graph G, List S){
	//int* time; &time
	////Sarah helped me write and debug this function
	if(G == NULL){ 
		exit(1);
	} 
	if(S == NULL){
		exit(1);
	} 
	if (length(S) != getOrder(G)){
		exit(1); 
	} 

	int time = 0;
    	for(int n = 1; n <= getOrder(G); n++){
		G->color[n] = WHITE; 
		G->parent[n] = NIL; 
		G->discover[n] = UNDEF; 
		G->finish[n] = UNDEF; 
	} 
			
	moveFront(S);
    	while(index(S) >= 0){
        	int u = get(S);
        	if (G->color[u] == WHITE){
            		visit(G, S, u, &time);
       		}
        	moveNext(S);
    	}

	for(int n = 1; n <= getOrder(G); n++){
		deleteBack(S); 
	} 
}	

Graph transpose(Graph G){
	//Sarah helped me write and debug this function
	if(G == NULL){
		exit(1); 
	} 
	Graph B = newGraph(getOrder(G));
       	for(int n = 1; n <= getOrder(G); n++){
		if(length(G->neighbors[n]) >= 0){
			moveFront(G->neighbors[n]); 
			while(index(G->neighbors[n]) >= 0){
				int x = get(G->neighbors[n]); 
				addArc(B, x, n); 
				moveNext(G->neighbors[n]); //Ishika helped me edit this function (added moveNext) 
			} 
		} 

	} 	
	return B;
       		
}

Graph copyGraph(Graph G){
        if(G == NULL){
                exit(1);
        }
        Graph B = newGraph(getOrder(G));
        for(int n = 1; n <= getOrder(G); n++){
                if(length(G->neighbors[n]) >= 0){
                        moveFront(G->neighbors[n]);
                        while(index(G->neighbors[n]) >= 0){
                                int x = get(G->neighbors[n]);
                                addArc(B, n, x);
                        	moveNext(G->neighbors[n]); //Ishika helped me edit this function (added moveNext)
			}
                }
        }
	return B; 
}

void printGraph(FILE* out, Graph G){
	if(G == NULL){
		exit(EXIT_FAILURE);
		return;
	}
	for(int i=1; i < getOrder(G)+1; i++){
		fprintf(out, "%d: ", i);
		/*while(index(G->neighbors[i]) != -1){
			fprintf(out, " %d", get(G->neighbors[i])); 
			moveNext(G->neighbors[i]); 
		} */ 
	       	printList(out, G->neighbors[i]);
		//fprintf(out, "\n");
	}
}



