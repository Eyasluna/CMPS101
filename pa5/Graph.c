//-----------------------------------------------------------------------------
//  Graph.c
//  Implementation file for Graph ADT
//  Yibo Fu
//  class:CMPS 101
//  professor:Tantalo
//  Graph ADT use List ADT to store vertices' parent/adj, this ADT supplies DFS, transpose of Graph, copyt of Graph and print Graph
//-----------------------------------------------------------------------------

#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj
{
   //graph variable
   int order;    //how many vertices are there
   int size;      //how many edges
   List *neighboor;  

   //DFS variable
   int *parent;   
   int *discover;
   int *finish;
   char *color;
   
} GraphObj;
//Constructor
//Create a new Graph with n vertices and no edges
Graph newGraph(int n)			//argument is number of vertices
{
   Graph G;
   int i;
   G=malloc(sizeof(GraphObj));
   G->order=n;       //number of vertices
   G->size=0;        //number of edges
   G->parent=calloc(n+1,sizeof(int));
   G->discover=calloc(n+1,sizeof(int));
   G->finish=calloc(n+1,sizeof(int));
   G->color=calloc(n+1,sizeof(char));
   G->neighboor=calloc(n+1,sizeof(List));

   for(i=1; i<=n; i++)
   {
      G->neighboor[i]=newList();
      G->parent[i]=NIL;
      G->color[i]='w';
   }
   return (G);
}
//Destructor
void freeGraph(Graph* pG)
{
   if(pG!=NULL && *pG!=NULL)
   {
     int i;
     for(i=1; i<=getOrder(*pG); i++)
      {
         freeList(&((*pG)->neighboor[i]));
      }
      free((*pG)->parent);
      free((*pG)->discover);
      free((*pG)->finish);
      free((*pG)->color);
      free((*pG)->neighboor);
	   free(*pG);
      *pG=NULL;
   }
}
//return order aka number of vertices
int getOrder(Graph G)
{
   return G->order;
}
//return size aka number of edges
int getSize(Graph G)
{
   return G->size;
}
//return BFS parent in
//procondition:1<u<order
int getParent(Graph G, int u) // Pre: 1<=u<=n=getOrder(G) 
{
   if(u<1||u>getOrder(G))
   {
      printf("Graph Error: calling getParent() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   return G->parent[u];
}
//return distance from source to distination
//precondition:distination int between 1<u<order
int getDiscover(Graph G, int u)
{
   if(u<1||u>getOrder(G))
   {
      printf("Graph Error: calling getDist() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   return G->discover[u];
}
int getFinish(Graph G, int u)
{
   if(u<1||u>getOrder(G))
   {
      printf("Graph Error: calling getDist() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   return G->finish[u];
}

/*** Manipulation procedures ***/
//directed edge from u to v only aka v in u's adj list
void addArc(Graph G, int u, int v)
{
   if(u<1||u>getOrder(G))
   {
      printf("Graph Error: calling addArc() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   else if(v<1||v>getOrder(G))
   {
      printf("Graph Error: calling addArc() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   moveFront(G->neighboor[u]);
   if(length(G->neighboor[u])==0)
   {
      append(G->neighboor[u],v);
   }
   while(index(G->neighboor[u])!=-1)
   {
      if(get(G->neighboor[u])>v)
      {
         insertBefore(G->neighboor[u],v);
         break;
      }
      moveNext(G->neighboor[u]);
      if(index(G->neighboor[u])==-1)
      {
         append(G->neighboor[u],v);
         break;
      }
   }
}
//add bi-directional edges for u and v vertices
void addEdge(Graph G, int u, int v)
{
   if(u<1||u>getOrder(G))
   {
      printf("Graph Error: calling addEdge() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   else if(v<1||v>getOrder(G))
   {
      printf("Graph Error: calling addEdge() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   else if(u==0||v==0)
   {
      return;
   }
   moveFront(G->neighboor[u]);
   if(length(G->neighboor[u])==0)
   {
      append(G->neighboor[u],v);
   }
   while(index(G->neighboor[u])!=-1)
   {
      if(get(G->neighboor[u])>v)
      {
         insertBefore(G->neighboor[u],v);
         break;
      }
      moveNext(G->neighboor[u]);
      if(index(G->neighboor[u])==-1)
      {
         append(G->neighboor[u],v);
         break;
      }
   }
   moveFront(G->neighboor[v]);
   if(length(G->neighboor[v])==0)
   {
      append(G->neighboor[v],u);
   }
   while(index(G->neighboor[v])!=-1)
   {
      if(get(G->neighboor[v])>u)
      {
         insertBefore(G->neighboor[v],u);
         break;
      }
      moveNext(G->neighboor[v]);
      if(index(G->neighboor[v])==-1)
      {
         append(G->neighboor[v],u);
         break;
      }
   }
   ++G->size;
}

//run Depth first search on Graph G with the ordering on List s
//precondition:length(S) == n
void DFS(Graph G, List s)
{
   int i;
   int time=0;
   int k=length(s);
   //check precondition
   if(length(s)!=getOrder(G))
   {
      printf("Graph Error: calling DFS() on Graph with length(s)!=number of vertices in the Graph");
      exit(1);
   }   
   for(i=1; i<=G->order; i++)
   {
      G->color[i]='w';
      G->parent[i]=NIL;
   }
   moveBack(s);
   for(i=1;i<=k;i++)
   {
      if(G->color[front(s)]=='w')
         Visit(G,s,&time,front(s));
      deleteFront(s);  
   }  
}
//local helper function for DFS
void Visit(Graph G, List s,int *time,int x)
{
   G->color[x]='g';         //x=get(s) if pass from DFS
   G->discover[x]=++*time;
   moveFront(G->neighboor[x]);
   while(index(G->neighboor[x])!=-1) //y=get(G->neighboor[get(s)])
   {
       if(G->color[get(G->neighboor[x])]=='w')
       {
          G->parent[get(G->neighboor[x])]=x;
          Visit(G,s,time,get(G->neighboor[x]));  
       }
       moveNext(G->neighboor[x]);
   }
   G->color[x]='b';
   G->finish[x]=++(*time);
   insertAfter(s,x); 
}
/*** Other operations ***/
//return transpose of graph G
Graph transpose(Graph G)
{
   int i;
   Graph tran=newGraph(getOrder(G));
   for(i=1; i<=getOrder(G); i++)
   {
      moveFront(G->neighboor[i]);
      while(index(G->neighboor[i])!=-1)
      {
         addArc(tran,get(G->neighboor[i]),i);
         moveNext(G->neighboor[i]);
      }
   }
   return tran;
}
//return copy of graph G
Graph copyGraph(Graph G)
{
   int i;
   Graph carbon=newGraph(getOrder(G));
   for(i=1; i<=getOrder(G); i++)
   {
      moveFront(G->neighboor[i]);
      while(index(G->neighboor[i])!=-1)
      {
         addArc(carbon,i,get(G->neighboor[i]));
         moveNext(G->neighboor[i]);
      }
   }
	return carbon;
}
//print Graph's neighboor list
void printGraph(FILE* out, Graph G)
{
   int i;
   for(i=1; i<=G->order; i++)
   {
      fprintf(out,"%d: ",i);
      printList(out,G->neighboor[i]);
      fprintf(out,"\n");
   }
}

