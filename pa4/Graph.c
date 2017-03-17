//-----------------------------------------------------------------------------
//  Implementation file for Graph ADT
//  An integer List ADT
//  Yibo Fu
//  CMPS 101
//  Graph ADT use List ADT to store vertices' parent/adj
//-----------------------------------------------------------------------------

#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj
{
   //graph variable
   int neworder;    //how many vertices are there
   int newsize;      //how many edges
   List *neighboor;
   int newsource;
   int *parent;   
   int *newdist;  //distance to source
   char *color;
   
} GraphObj;
//Constructor
//Create a new Graph with n vertices and no edges
Graph newGraph(int n)
{
   Graph G;
   int i;
   G=malloc(sizeof(GraphObj));
   G->neworder=n;       //number of vertices
   G->newsize=0;        //number of edges
   G->newsource=NIL;		//default source is non-existence since no BFS is being use yet
   G->parent=calloc(n+1,sizeof(int));
   G->newdist=calloc(n+1,sizeof(int));
   G->color=calloc(n+1,sizeof(char));
   G->neighboor=calloc(n+1,sizeof(List));

   for(i=1; i<=n; i++)
   {
      G->neighboor[i]=newList();
      G->parent[i]=NIL;
      G->newdist[i]=INF;
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
      free((*pG)->newdist);
      free((*pG)->color);
      free((*pG)->neighboor);
	  free(*pG);
      *pG=NULL;
   }
}
//return order aka number of vertices
int getOrder(Graph G)
{
   return G->neworder;
}
//return size aka number of edges
int getSize(Graph G)
{
   return G->newsize;
}
//return source from the BFS search
int getSource(Graph G)
{
   return G->newsource;
}
//return BFS parent in
//procondition:1<u<order
int getParent(Graph G, int u)
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
int getDist(Graph G, int u)
{
   if(u<1||u>getOrder(G))
   {
      printf("Graph Error: calling getDist() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   return G->newdist[u];
}
//appends to the List L the vertices of a shortest path in G from source to u
//precondition:BFS called, 1<u<order
void getPath(List L, Graph G, int u)
{
   if(getSource(G)==NIL)
   {      
      printf("Graph Error: calling getPath() on Graph without call BFS before");
      exit(1);
   }
   else if(u<1||u>getOrder(G))
   {
      printf("Graph Error: calling getPath() on Graph with a vertice number doesn't exist");
      exit(1);
   }
   else if(getSource(G)==u)
   {
      prepend(L,u);
      return;
   }
   else if(getParent(G,u)==NIL)
   {
      append(L,INF);
      return;
   }
   else
   {
      getPath(L,G,getParent(G,u));
      append(L,u);
   }
}
/*** Manipulation procedures ***/
//deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G)
{
   int i;
   for(i=1; i<=getOrder(G); i++)
   {
      clear(G->neighboor[i]);
      G->parent[i]=NIL;
      G->newdist[i]=INF;
      G->color[i]='w';
   }
   G->newsize=0;
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
   ++G->newsize;
}

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
//run Breath first search on Graph g with source s
void BFS(Graph G, int s)
{
   int x;
   int i;
   List Q;
   G->newsource=s;
   for(i=1; i<=G->neworder; i++)
   {
      G->color[i]='w';
      G->newdist[i]=INF;
      G->parent[i]=NIL;
   }
   G->color[s]='g';
   G->newdist[s]=0;
   G->parent[s]=NIL;
   Q=newList();
   append(Q,s);
   while(length(Q)!=0)
   {
      moveFront(Q);        //dequeue
      x=get(Q);            //dequeue
      deleteFront(Q);      //dequeue
      moveFront(G->neighboor[x]);
      while(index(G->neighboor[x])!=-1)
      {
         if(G->color[get(G->neighboor[x])]=='w')
         {
            G->color[get(G->neighboor[x])]='g';
            G->newdist[get(G->neighboor[x])]=G->newdist[x]+1;
            G->parent[get(G->neighboor[x])]=x;
            append(Q,get(G->neighboor[x]));
            moveNext(G->neighboor[x]);
         }
         else
         {
            moveNext(G->neighboor[x]);
         }
      }
      G->color[x]='b';
   }
   freeList(&Q);
}
/*** Other operations ***/
//print Graph's parent list
void printGraph(FILE* out, Graph G)
{
   int i;
   for(i=1; i<=G->neworder; i++)
   {
      fprintf(out,"%d:",i);
      printList(out,G->neighboor[i]);
      fprintf(out,"\n");
   }
}

