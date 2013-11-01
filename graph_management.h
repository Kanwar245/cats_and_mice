/*
  UTSC, CSC B63 - Assignment 4, Winter 2012

  This file contains the structure and function definitions needed
  to handle graphs.

  You don't need to modify this file, but be sure to understand
  everything here.

  Updated by F. Estrada, March, 2012
*/

#ifndef __graph_management_header
#define __graph_management_header

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "imageUtils.h"
#include "GameAI.h"

/*
   Simple structure to hold paths in the graph as linked lists of
   (x,y) coordinates to be visited by some agent
*/
struct path_node{
	int x;
	int y;
	struct path_node *next;
};

struct path_node *newPathNode(int x, int y);
/*
   Small function to help you allocate new path nodes as needed
   for the shortest path algorithm and game behaviour functions
*/

void deletePath(struct path_node *path);
/*
   Deletes a path (consisting of a linked list of path nodes)
*/

void initGraph(float A[GsizeSqr][GsizeSqr], int minMouse2GateDist, int minCat2MouseDist, int GamePos[numAgents][3]);
/*
   Initializes the graph representing the game grid. The graph
   represents a square grid of (x,y) positions. We don't actually
   store the grid itself, only an adjacency matrix representing
   a graph with one node per grid position.

   Each grid position has a corresponding graph node. Nodes are
   connected to at most their 4 immediate neighbours: up, down,
   left and right. A holds an adjacency matrix that encodes the
   connections. We initially set A to be a matrix of random
   weights and will use Prim's MST algorithm to select only a
   subset of edges from A.

   After running Prim's algorithm, nodes will no longer be always
   connected to their 4 neighbours, instead, some neighbours will
   have been disconnected. Disconnected neighbours correspond to
   locations in the grid that have a wall between them.

   This function also sets up the initial position
   for the 'player' (mouse), and the 'adversaries' (kittys) as
   well as the gate and the cheese. 

   The nAgents array is used to keep track of the positions of
   each agent. By definition:

   GamePos[0][:] is the position of the gate
   GamePos[1][:] is the position of the mouse
   GamePos[2][:] is the position of the cheese
   GamePos[3 - (numAgents-1)][:] give the positions of the kitties

   For each row, GamePos[:][0] is the x grid coordinate for the agent
                 GamePos[:][1] is the y grid coordinate for the agent
                 GamePos[:][2] is the mode of agent behaviour (see Cats_and_Mice.c)
*/

void addLoops(float A[GsizeSqr][GsizeSqr], int nLoops);
/*
  Adds loop to the graph after you have created an MST.
  A graph without loops would have a single path between
  any pair of nodes making things rather difficult for the
  mouse
*/

void graphToMaze(float A[GsizeSqr][GsizeSqr], struct image *im, unsigned char R, unsigned char G, unsigned char B);
/*
  Takes an input adjacency matrix that represents the graph
  and produces a maze image with walls between disconnected
  graph nodes, and no walls between connected nodes
 
  You can change the wall colour by specifying the R,G,B
  values of the colour you want (in [0, 255])
*/

void PacoPrim(float A[GsizeSqr][GsizeSqr]);
struct path_node *PacoShortestPath(float A[GsizeSqr][GsizeSqr], int xi, int yi, int xf, int yf);

#endif
