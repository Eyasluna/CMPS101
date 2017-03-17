//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//  Yibo Fu
//  class:CMPS 101
//  Graph ADT use List ADT to store vertices' parent/adj
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"
#define INF -1
#define NIL 0

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;
// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);
// Access functions -----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List s);
void Visit(Graph G, List s,int *time,int current);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
#endif