//-----------------------------------------------------------------------------
// FindPath.c
//main that uses Graph ADT and List ADT
//  Yibo Fu
//  CMPS 101
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]) {
   FILE *in, *out;
   char line[MAX_LEN];
   char* token;
   Graph G;
   List L=newList();
   int newvert1=1;
   int newvert2=1;

   // check command line for correct number of arguments
   if( argc != 3 ){
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
   while(newvert1!=0) {
      fgets(line,MAX_LEN,in);
      token=strtok(line," \n");
      newvert1=atoi(token);
      if(newvert1==0)				//take first vertex
         break;
      token=strtok(NULL," \n");
      newvert2=atoi(token);        //take second vertex
     addEdge(G,newvert1,newvert2);
   }
   printGraph(out,G);
   fprintf(out,"\n");
   
   //just finish adding edges, now do BFS and get distance
   newvert1=1;
   while(newvert1!=0) {
      fgets(line,MAX_LEN,in);
      token=strtok(line," \n");
	  newvert1=atoi(token);				//get the first int on that line, call it source
	  if(newvert1==0)
         break;
      BFS(G,newvert1);				//do BFS with given source
	  
      token=strtok(NULL," \n");	
      newvert2=atoi(token);				//get the second int on that line,call it destination
      if(getDist(G,newvert2)!=INF)	{		//if source and destination is connected{
         fprintf(out,"The distance from %d to %d is %d\n",newvert1,newvert2,getDist(G,newvert2));
         fprintf(out,"A shortest %d-%d path is:",newvert1,newvert2);
         clear(L);
         getPath(L,G,newvert2);
         printList(out,L);
         fprintf(out,"\n\n");
      }
      else		//if source and destination is disconnected
      {
         fprintf(out,"The distance from %d to %d is infinity\n",newvert1,newvert2);
         fprintf(out,"No %d-%d path exists\n\n",newvert1,newvert2);
      }
   }
   /* close files */
   freeGraph(&G);
   freeList(&L);
   fclose(in);
   fclose(out);

   return(0);
}
