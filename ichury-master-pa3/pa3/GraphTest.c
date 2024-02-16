/****************************************************************************************
*  GraphTest.c 
*  Test client used to seperate functions in Graph.c in isolation   
*  Isha Chury 
*  ichury
*  pa3 
*****************************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include "List.h" 
#include "Graph.h" 

int main(int argc, char* argv[]){
	Graph A = newGraph(6);
        List AA = newList();
	for(int i=1; i<=6; i++){
                append(AA, i);
        }
	addEdge(A, 1, 2);
       	addEdge(A, 1, 5); 
	addEdge(A, 3, 2);
	addEdge(A, 3, 5); 
	addEdge(A, 5, 6); 
	addEdge(A, 3, 6); 
	addEdge(A, 5, 4); 
	addEdge(A, 4, 1); 
	DFS(A, AA);
        fprintf(stdout, "Input List: \n");
        printList(stdout, AA);
        fprintf(stdout, "\n");
        fprintf(stdout, "DFS of Graph A: \n");
        fprintf(stdout, "x:  d  f  p\n");
        for(int i=1; i<=6; i++){
                fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(A, i), getFinish(A, i), getParent(A, i));
        }
        fprintf(stdout, "\n");
        fprintf(stdout, "Graph A Adjacency List: \n");
        printGraph(stdout, A);
        fprintf(stdout, "\n");
        fprintf(stdout, "Copy of Graph A: \n");
        printGraph(stdout, copyGraph(A));
        fprintf(stdout, "\n");
        fprintf(stdout, "Graph Transpose of A: \n");
        printGraph(stdout, transpose(A));
	
	Graph T = transpose(A); 
        DFS(T, AA);
   	fprintf(stdout, "\n");
	fprintf(stdout, "DFS of Tranpose (Graph A): \n"); 
   	fprintf(stdout, "x:  d  f  p\n");
   	for(int i=1; i<=6; i++){
      		fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   	}
   	fprintf(stdout, "\n");
	freeList(&AA);
        freeGraph(&A);

	fprintf(stdout, "\n"); 

	Graph G = newGraph(8);
	List S = newList(); 
	for(int i=1; i<=8; i++){
		append(S, i);
	} 	
	addEdge(G, 1, 2); 
	addEdge(G, 2, 3); 
	addEdge(G, 3, 4); 
	addEdge(G, 4, 5); 
	addEdge(G, 4, 1); 
	addEdge(G, 5, 1); 
	addEdge(G, 2, 6); 
	addEdge(G, 6, 7); 
	addEdge(G, 7, 2); 
	addEdge(G, 3, 7); 
	addEdge(G, 8, 7); 
	addEdge(G, 8, 3); 
	addEdge(G, 4, 8); 
	addEdge(G, 5, 8); 
	DFS(G, S);
	fprintf(stdout, "Input List: \n"); 
	printList(stdout, S); 
   	fprintf(stdout, "\n");
	fprintf(stdout, "DFS of Graph G: \n"); 
	fprintf(stdout, "x:  d  f  p\n");
   	for(int i=1; i<=8; i++){
      		fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   	}
	fprintf(stdout, "\n"); 
	fprintf(stdout, "Graph G Adjacency List: \n"); 
	printGraph(stdout, G); 
	fprintf(stdout, "\n"); 
	fprintf(stdout, "Copy of Graph G: \n"); 
	printGraph(stdout, copyGraph(G)); 
	fprintf(stdout, "\n");
        fprintf(stdout, "Graph Transpose of G: \n"); 
	printGraph(stdout, transpose(G));

	freeList(&S); 
	freeGraph(&G);

}

/* Output 
Input List:
1 2 3 5 6 4

DFS of Graph A:
x:  d  f  p
1:  1 12  0
2:  2 11  1
3:  3 10  2
4:  5  6  5
5:  4  9  3
6:  7  8  5

Graph A Adjacency List:
1: 2 4 5
2: 1 3
3: 2 5 6
4: 1 5
5: 1 3 4 6
6: 3 5

Copy of Graph A:
1: 2 4 5
2: 1 3
3: 2 5 6
4: 1 5
5: 1 3 4 6
6: 3 5

Graph Transpose of A:
1: 2 4 5
2: 1 3
3: 2 5 6
4: 1 5
5: 1 3 4 6
6: 3 5

DFS of Tranpose (Graph A):
x:  d  f  p
1:  1 12  0
2:  2 11  1
3:  3 10  2
4:  5  6  5
5:  4  9  3
6:  7  8  5


Input List:
1 2 3 4 5 8 7 6

DFS of Graph G:
x:  d  f  p
1:  1 16  0
2:  2 15  1
3:  3 14  2
4:  4 13  3
5:  5 12  4
6:  8  9  7
7:  7 10  8
8:  6 11  5

Graph G Adjacency List:
1: 2 4 5
2: 1 3 6 7
3: 2 4 7 8
4: 1 3 5 8
5: 1 4 8
6: 2 7
7: 2 3 6 8
8: 3 4 5 7

Copy of Graph G:
1: 2 4 5
2: 1 3 6 7
3: 2 4 7 8
4: 1 3 5 8
5: 1 4 8
6: 2 7
7: 2 3 6 8
8: 3 4 5 7

Graph Transpose of G:
1: 2 4 5
2: 1 3 6 7
3: 2 4 7 8
4: 1 3 5 8
5: 1 4 8
6: 2 7
7: 2 3 6 8
8: 3 4 5 7 */ 
