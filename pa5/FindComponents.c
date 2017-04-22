//-----------------------------------------------------------------------------
// FindComponents.c
// main that uses Graph ADT and List ADT
//  Yibo Fu
//  class:CMPS 101
//  takes input and do DFS and can tell the strongly connected components on input Graph
//-----------------------------------------------------------------------------
// test
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

#define MAX_LEN 160

int main(int argc, char * argv[])
{
   FILE *in, *out;
   char line[MAX_LEN];
   char* token;
   Graph G,GT;
   List S=newList();
   int vert1=1;
   int vert2=1;
   int i;
   int nilparentcount;
   List *SCC;
   int listcounter=1;

   // check command line for correct number of arguments
   if( argc != 3 )
   {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   //first start by reading first line which is the number of vertices Graph will have
   fgets(line,MAX_LEN,in);
   token=strtok(line," \n");
   G=newGraph(atoi(token));
   //done making graph with the right number of vertex
   while(vert1!=0)
   {
      fgets(line,MAX_LEN,in);
      token=strtok(line," \n");
      vert1=atoi(token);
      if(vert1==0)				//take first vertex
         break;
      token=strtok(NULL," \n");
      vert2=atoi(token);        //take second vertex
     addArc(G,vert1,vert2);
   }
   fprintf(out,"Adjacency list representation of G:\n");
   printGraph(out,G);
   fprintf(out,"\n");
   //finish adding edge
   for(i=1; i<=getOrder(G); i++) append(S, i);
   //List is ready
   DFS(G,S);
   GT=transpose(G);
   DFS(GT,S);
   //tanspose of G now store in as GT
   moveFront(S);
   nilparentcount=0;    //this variable store the vertices with NIL parent
   for(i=1; i<=getOrder(G); i++)
   {
      if(getParent(GT,i)==NIL)
      {
         nilparentcount++;
      }
   }
   //finish getting SCC array size which is from nilparentcount
   SCC=calloc(nilparentcount+1,sizeof(List));         //allocate memory for SCC
   //just alocated memory for SCC
   for(i=1; i<=nilparentcount; i++)
   {
      SCC[i]=newList();
   }
   moveBack(S);                           //starts fromt he back of the stack
   for(i=1; i<=getOrder(G); i++)
   {
      prepend(SCC[listcounter],get(S)); 
      if(getParent(GT,get(S))==NIL)    //if the stack hits Nil parent, shift to the next List in the array 
         listcounter++;          
      movePrev(S);
   }
   //Strongly connected components print out
   fprintf(out,"G contains %d strongly connected components:\n",nilparentcount);
   for(i=1; i<=nilparentcount; i++)
   {
      fprintf(out,"Component %d: ",i);
      printList(out,SCC[i]);
      fprintf(out,"\n");
      freeList(&SCC[i]);
    }

   //destruction
   freeGraph(&G);
   freeGraph(&GT);
   freeList(&S);
   free(SCC);
   fclose(in);
   fclose(out);
   return(0);
}