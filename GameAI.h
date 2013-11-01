/*
  UTSC - CSC B63 Winter 2012

  This file provides the function templates and data structures
  used for the Game AI assignment. You need to read and understand
  the contents of this file.

  Updated by F. Estrada, March 2, 2012
*/

#ifndef __gameAI_header
#define __gameAI_header

#include<math.h>
#define numLoops 150		// Number of loops to add to graph. Adding more or fewer loops makes the mazes
				// easier or harder respectively. I've tried with 50, 100, and 150 (more gets
				// too easy for the cats since they can go straight for the mouse).
#define maxFrames 200		// Maximum number of simulation steps (avoids endless loops)
#define numAgents 8             // Number of agents, 3 + number of kitties
#define hearingRadius 20         // Max. distance at which cats can hear the mouse

// In general, you should not change the settings below. If you do, your code will not produce the expected
// results, may crash, and will cost you plenty of marks.
#define Gsize 20                // Size of the grid is Gsize x Gsize
#define GsizeSqr 400            // Graph size squared
#define Psize 30                // Size of grid element in pixels ** don't mess with this **
#define frameSize 600           // Must be Gsize*Psize ** don't mess with this either **

// Mind the order of the includes. graph_management.h requires the above defines to be present
#include "graph_management.h"
#include "graph_algorithms.h"
#include "imageUtils.h"

void loadSprites(struct image *sprites[numAgents]);
/*
  Loads the game sprites from files
*/

void renderFrame(int GamePos[numAgents][3], struct image *sprites[numAgents], struct image *maze, struct path_node *path, int frameno);
/*
  Generates a single frame using the maze, and the current positions
  of each agent. The frame is output to disk and an attempt is made
  to convert the frame to .jpg format. If the conversion is
  successful the .ppm file is removed to save space.
*/

void renderPath(struct image *maze, struct path_node *path, unsigned char R, unsigned char G, unsigned char B, int updateSource);
/*
  Plots the specified path onto the maze and outputs the image to
  disk. Use this function for debugging your shortest path
  code.

  Depending on the value of updateSource:
  if 0 - writes the path image to disk, does not update 'ref'
  otherwise - updates 'ref' and does not output to disk.
*/

void updateAgentPotisions(int GamePos[numAgents][3], float A[GsizeSqr][GsizeSqr],int mode);
/*
  Manages the position updates for different agents
*/

#endif
