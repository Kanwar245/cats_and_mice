/*
  UTSC, CSC B63 - Winter 2012

  This is the header file for the graph algorithms
  module. This is the module where you must implement
  the required graph manipulation algorithms, in
  particular:

  PrimMST - computes an MST using Prim's method
  shortestPath - computes (and returns) the shortest
                 path between two nodes using Dijkstra's
                 method

  Be sure to thoroughly comment your solution and explain
  how it works.

  You will need to become familiar with the functions
  provided to you in

  graph_management.h

  F.J.E., March 2012
*/

#ifndef __graph_algorithms_header
#define __graph_algorithms_header

#include "graph_management.h"

void PrimMST(float A[GsizeSqr][GsizeSqr]);
void findNeighbour(int pos, float *priority, int *predecessor, struct heap *h, float A[GsizeSqr][GsizeSqr], int status);
struct path_node *shortestPath(float A[GsizeSqr][GsizeSqr], int xi, int yi, int xf, int yf);

#endif
