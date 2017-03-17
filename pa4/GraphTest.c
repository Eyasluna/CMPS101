//-----------------------------------------------------------------------------
// Personal test class for Graph adt
//  Yibo Fu
//  class:CMPS 101
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[])
{
   List L=newList();
   Graph G = newGraph(6);
   addEdge(G,1,2);
   addEdge(G,1,3);
   addEdge(G,2,4);
   addEdge(G,2,5);
   addEdge(G,2,6);
   addEdge(G,3,4);
   addEdge(G,4,5);
   addEdge(G,5,6);
   BFS(G,1);
   fprintf(stdout,"getParent(1):%d\n",getParent(G,1));
   fprintf(stdout,"getParent(2):%d\n",getParent(G,2));
   fprintf(stdout,"getParent(3):%d\n",getParent(G,3));
   fprintf(stdout,"getParent(4):%d\n",getParent(G,4));
   fprintf(stdout,"getParent(5):%d\n",getParent(G,5));
   fprintf(stdout,"getParent(6):%d\n",getParent(G,6));

   fprintf(stdout,"getDist(1):%d\n",getDist(G,1));
   fprintf(stdout,"getDist(2):%d\n",getDist(G,2));
   fprintf(stdout,"getDist(3):%d\n",getDist(G,3));
   fprintf(stdout,"getDist(4):%d\n",getDist(G,4));
   fprintf(stdout,"getDist(5):%d\n",getDist(G,5));
   fprintf(stdout,"getDist(6):%d\n",getDist(G,6));
   getPath(L,G,1);
   printList(stdout,L);
   clear(L);
   printf("\n");
   getPath(L,G,2);
   printList(stdout,L); 
   clear(L);
   printf("\n");
   getPath(L,G,3);
   printList(stdout,L);
   clear(L);
   printf("\n");
   getPath(L,G,4);
   printList(stdout,L);
   clear(L);
   printf("\n");
   getPath(L,G,5);
   printList(stdout,L);
   clear(L);
   printf("\n");
   getPath(L,G,6);
   printList(stdout,L);
   clear(L);
   printf("\n");
   printGraph(stdout,G);
   freeGraph(&G);



   return(0);
}