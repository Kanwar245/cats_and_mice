/*
  UTSC, CSC B63 - Winter 2012

  This is the implementation file for the graph algorithms
  module. Complete *ALL* sections marked "TO DO". Be sure
  to read and follow all instructions in the handout, and
  make sure your functions return what is expected.

  Your code must compile and run for it to be marked.
  It is not possible for your TA to assign partial marks
  to non-working code since the algorithms being implemented
  are fairly complex. Remember: Your TA is not a compiler!

  You have two main methods to implement:

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

#include "graph_algorithms.h"
#include "my_heaps.h"

void PrimMST(float A[GsizeSqr][GsizeSqr])
{
 /*
   You must complete this function to carry out Prim's algorithm
   and produce an MST from the graph represented by the adjacency
   matrix A.

   There are two ways to go:
   - The slow way using the adjacency matrix directly
   - The fast way using priority heaps

   Choose whichever one you like, but note they are worth different
   amounts. The heap-based method is required for full marks. See
   the handout for details.

   NOTE:
   * DO NOT * add heap code outside my_heap.[c,h]

   Once you have computed the MST, be sure to update A[][] to
   contain the MST, and also make sure that all edges in the
   MST have weight 1. In other words, after we compute the MST
   we will no longer care about random weights since the cost
   of moving from one space in the maze to the next should
   always be one.
 */
	
	int n[GsizeSqr];		/*holds the nodes*/
	int predecessor[GsizeSqr];	/*holds the precesessors of each node*/
	int MST[GsizeSqr][2], v = GsizeSqr;
	float p[GsizeSqr];	/*holds the cheapest weights from every node*/
	int i, j, l, m, s, k;
	for(i = 0; i < v; i++) {
		n[i] = i;				/*node is value of index*/		
		p[i] = 10e7;			/*huge number*/
		predecessor[i] = NULL;	/*not in the tree initially*/
	}

	/*need to build a heap containing PQ nodes*/
	struct heap *h = buildHeap(n, p, GsizeSqr);
	/*implement prim's algorithm from this point on*/
	s = dequeue(h);
	/*Find all neighbours of s*/
	findNeighbour(s, p, predecessor, h, A, 0);
	while (!isEmpty(h)) {
		k = dequeue(h);
		MST[k][0] = k;
		MST[k][1] = predecessor[k];
		/*peek at the neighbours*/
		findNeighbour(k, p, predecessor, h, A, 1);
	}
	/*initialize the adjacency matrix to a null(containing all zeroes) matrix*/
	for(j = 0; j < GsizeSqr; j++) {
		for (l = 0; l < GsizeSqr; l++) {
			A[j][l] = 0;
		}
	}
	/*re-initialize the null matrix to contain 1.0 for only those neighbours we found*/
	for (m = 0; m < GsizeSqr; m++) {
		A[MST[m][0]][MST[m][1]] = 1.0;
		A[MST[m][1]][MST[m][0]] = 1.0;
	}
	/*deallocate the memory used by the heap*/
	free(h);
}

/*helper function for Prim in order to find the neighbours of all nodes in heap*/
void findNeighbour(int pos, float *p, int *predecessor, struct heap *h, float A[GsizeSqr][GsizeSqr], int status) {

	/*if position value is less than Gsize then we are at the top of the maze, and will have no top neighbours*/
	if (pos < Gsize) {
		/*the first position in the maze will have bottom and right neighbours*/
		if (pos == 0) {
			/*if right node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+1] > A[pos][pos+1]) && status) {
				p[pos+1] = A[pos][pos+1];
				predecessor[pos+1] = pos;
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+1] = A[pos][pos+1];
				decreasePriority(h, pos+1, p[pos+1]);
			}

			/*if bottom node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+Gsize] > A[pos][pos+Gsize]) && status) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				predecessor[pos+Gsize] = pos;
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
		}

		/*the node in the first row and last column of the maze will only have bottom and left neighbours*/
		else if (pos == (Gsize-1)) {
			/*if left node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-1] > A[pos][pos-1]) && status) {
				p[pos-1] = A[pos][pos-1];
				predecessor[pos-1] = pos;
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-1] = A[pos][pos-1];
				decreasePriority(h, pos-1, p[pos-1]);
			}

			/*if bottom node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+Gsize] > A[pos][pos+Gsize]) && status) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				predecessor[pos+Gsize] = pos;
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
		}

		/*the node is somewhere in the middle of the first row and has bottom, left, and right neighbours*/
		else {
			/*if bottom node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+Gsize] > A[pos][pos+Gsize]) && status) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				predecessor[pos+Gsize] = pos;
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			
			/*if left node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-1] > A[pos][pos-1]) && status) {
				p[pos-1] = A[pos][pos-1];
				predecessor[pos-1] = pos;
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-1] = A[pos][pos-1];
				decreasePriority(h, pos-1, p[pos-1]);
			}

			/*if right node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+1] > A[pos][pos+1]) && status) {
				p[pos+1] = A[pos][pos+1];
				predecessor[pos+1] = pos;
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+1] = A[pos][pos+1];
				decreasePriority(h, pos+1, p[pos+1]);
			}
		}
	}

	/*the position is at the bottom of the maze and will have no bottom neighbours*/
	else if (pos >= (GsizeSqr-Gsize)) {
		/*the position is the first one in the last row and will only have top and right neighbours*/
		if (pos == (GsizeSqr-Gsize)) {
		/*if top node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-Gsize] > A[pos][pos-Gsize]) && status) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				predecessor[pos-Gsize] = pos;
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*if right node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+1] > A[pos][pos+1]) && status) {
				p[pos+1] = A[pos][pos+1];
				predecessor[pos+1] = pos;
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+1] = A[pos][pos+1];
				decreasePriority(h, pos+1, p[pos+1]);
			}
		}

		/*the positon is the last one in the maze and will only have top and left neighbours*/
		else if (pos == (GsizeSqr-1)) {
			/*if top node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-Gsize] > A[pos][pos-Gsize]) && status) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				predecessor[pos-Gsize] = pos;
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*if left node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-1] > A[pos][pos-1]) && status) {
				p[pos-1] = A[pos][pos-1];
				predecessor[pos-1] = pos;
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-1] = A[pos][pos-1];
				decreasePriority(h, pos-1, p[pos-1]);
			}
		}

		/*the position is somewhere in the middle at the bottom and will have left, top, and right neighbours*/
		else {
			/*if left node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-1] > A[pos][pos-1]) && status) {
				p[pos-1] = A[pos][pos-1];
				predecessor[pos-1] = pos;
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-1] = A[pos][pos-1];
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*if top node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-Gsize] > A[pos][pos-Gsize]) && status) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				predecessor[pos-Gsize] = pos;
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*if right node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+1] > A[pos][pos+1]) && status) {
				p[pos+1] = A[pos][pos+1];
				predecessor[pos+1] = pos;
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+1] = A[pos][pos+1];
				decreasePriority(h, pos+1, p[pos+1]);
			}
		}
	}

	/*if position value is a multiple of Gsize then we are at the left of the maze, and will have no left neighbours*/
	else if ((pos%Gsize) == 0) {
		/*the first position in the maze will have bottom and right neighbours*/
		if (pos == 0) {
			/*if right node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+1] > A[pos][pos+1]) && status) {
				p[pos+1] = A[pos][pos+1];
				predecessor[pos+1] = pos;
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+1] = A[pos][pos+1];
				decreasePriority(h, pos+1, p[pos+1]);
			}

			/*if bottom node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+Gsize] > A[pos][pos+Gsize]) && status) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				predecessor[pos+Gsize] = pos;
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
		}

		/*the position is the first one in the last row and will only have top and right neighbours*/
		else if (pos == (GsizeSqr-Gsize)) {
			/*if top node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-Gsize] > A[pos][pos-Gsize]) && status) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				predecessor[pos-Gsize] = pos;
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*if right node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+1] > A[pos][pos+1]) && status) {
				p[pos+1] = A[pos][pos+1];
				predecessor[pos+1] = pos;
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+1] = A[pos][pos+1];
				decreasePriority(h, pos+1, p[pos+1]);
			}
		}
		
		/*the position is somewhere in the middle of the left side of the maze and will have top, right, and bottom neighbours*/
		else {
			/*if top node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-Gsize] > A[pos][pos-Gsize]) && status) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				predecessor[pos-Gsize] = pos;
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*if right node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+1] > A[pos][pos+1]) && status) {
				p[pos+1] = A[pos][pos+1];
				predecessor[pos+1] = pos;
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+1] = A[pos][pos+1];
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*if bottom node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+Gsize] > A[pos][pos+Gsize]) && status) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				predecessor[pos+Gsize] = pos;
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
		}
	}

	/*the position is on the right side of the maze and will have no right neighbours*/
	else if ((pos%Gsize) == (Gsize-1)) {
		/*is position is the last one on the first row of the maze, it'll have no top neighbour*/
		if (pos == (Gsize-1)) {
			/*if left node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-1] > A[pos][pos-1]) && status) {
				p[pos-1] = A[pos][pos-1];
				predecessor[pos-1] = pos;
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-1] = A[pos][pos-1];
				decreasePriority(h, pos-1, p[pos-1]);
			}

			/*if bottom node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+Gsize] > A[pos][pos+Gsize]) && status) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				predecessor[pos+Gsize] = pos;
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
		}

		/*the positon is the last one in the maze and will only have top and left neighbours*/
		else if (pos == (GsizeSqr-1)) {
			/*if top node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-Gsize] > A[pos][pos-Gsize]) && status) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				predecessor[pos-Gsize] = pos;
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*if left node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-1] > A[pos][pos-1]) && status) {
				p[pos-1] = A[pos][pos-1];
				predecessor[pos-1] = pos;
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-1] = A[pos][pos-1];
				decreasePriority(h, pos-1, p[pos-1]);
			}
		}

		/*the position is somewhere in the middle of the right side and will have top, left, and bottom neighbours*/
		else {
			/*if top node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-Gsize] > A[pos][pos-Gsize]) && status) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				predecessor[pos-Gsize] = pos;
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*if left node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-1] > A[pos][pos-1]) && status) {
				p[pos-1] = A[pos][pos-1];
				predecessor[pos-1] = pos;
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-1] = A[pos][pos-1];
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*if bottom node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+Gsize] > A[pos][pos+Gsize]) && status) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				predecessor[pos+Gsize] = pos;
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
		}
	}

	/*the position is somewhere in the middle of the maze and will therefore all four neighbours*/
	else {
			/*if left node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-1] > A[pos][pos-1]) && status) {
				p[pos-1] = A[pos][pos-1];
				predecessor[pos-1] = pos;
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-1] = A[pos][pos-1];
				decreasePriority(h, pos-1, p[pos-1]);
			}
			/*if top node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos-Gsize] > A[pos][pos-Gsize]) && status) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				predecessor[pos-Gsize] = pos;
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos-Gsize] = A[pos][pos-Gsize];
				decreasePriority(h, pos-Gsize, p[pos-Gsize]);
			}
			/*if right node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+1] > A[pos][pos+1]) && status) {
				p[pos+1] = A[pos][pos+1];
				predecessor[pos+1] = pos;
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+1] = A[pos][pos+1];
				decreasePriority(h, pos+1, p[pos+1]);
			}
			/*if bottom node's priority is greater and is in a loop, update its priority and predecessor*/
			if ((p[pos+Gsize] > A[pos][pos+Gsize]) && status) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				predecessor[pos+Gsize] = pos;
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
			/*otherwise no need to update predecessor*/
			else if (status == 0) {
				p[pos+Gsize] = A[pos][pos+Gsize];
				decreasePriority(h, pos+Gsize, p[pos+Gsize]);
			}
		}
}

struct path_node *shortestPath(float A[GsizeSqr][GsizeSqr], int xi, int yi, int xf, int yf)
{
 /*
   Solves for the shortest path between grid point (xi,yi) and (xf,yf)
   on the graph encoded by A using Dijkstra's shortest path method.

   The shortest path is returned as a linked list of nodes to be visited.

   Refer to the CLRS textbook for details on how to implement the shortest
   path method.

   There's two possible ways to go here:

   - The slow method using the adjacency matrix A directly.
   - The fast method using priority heaps (if you already wrote code for priority
     heaps for Prim's method, it's probably worth your while to use it here)

   For full marks, you need to implement the fast version. See the handout for
   details.

   In general, you will need to keep track of visited nodes, and the predecessor
   for each node that has been explored while computing the shortest path.

   //////////////////////////////
   // Very important: You must produce a linked list of nodes describing the path
   //                 from (xi,yi) to (xf,yf) including the endpoints. The list
   //                 should describe the path to be followed in the correct order
   //                 and will be used by the main function to update agent
   //                 positions.
   //////////////////////////////
 */

	if (xi<0||xi>=Gsize&&yi<0&&yi>=Gsize||xf<0||xf>=Gsize||yf<0||yf>=Gsize)
	{
  		fprintf(stderr,"shortestPath(): Endpoint(s) outside of the graph!\n");
  		return(NULL);
 	}
	
	int predecessor[GsizeSqr], n[GsizeSqr], d[GsizeSqr];
	float p[GsizeSqr], v = GsizeSqr;
	int i, j, m;
	
	for(i = 0; i < v; i++) {
		predecessor[i] = NULL;	/*no predecessor yet*/
		p[i] = 10e7;			/*huge number*/
		n[i] = i;				/*nodes*/
	}
	p[0] = 0;	/*initialize starting node's priority*/
	struct heap *h = buildHeap(n, p, Gsize*Gsize);
	/*implement Djikstra's algorithm*/
	while (!isEmpty(h)) {
		m = dequeue(h);
		/*node has no top neighbour*/
		if (m < Gsize) {
			/*first node in graph*/
			if (m == 0) {
				/*has a bottom neighbour*/
				if ((p[m] + A[m][m+Gsize] < p[m+Gsize]) && A[m][m+Gsize]) {
				p[m+Gsize] = A[m][m+Gsize] + p[m];
				predecessor[m+Gsize] = m;
				decreasePriority(h, m+Gsize, p[m+Gsize]);
				}
				/*has a right neighbour*/
				if ((p[m] + A[m][m+1] < p[m+1]) && A[m][m+1]) {
					p[m+1] = A[m][m+1] + p[m];
					predecessor[m+1] = m;
					decreasePriority(h, m+1, p[m+1]);
				}
			}
			/*last node on the top row (has no right neighbour)*/
			else if (m == Gsize-1) {
				/*has a left neighbour*/
				if ((p[m] + A[m][m-1] < p[m-1]) && A[m][m-1]) {
					p[m-1] = A[m][m-1] + p[m];
					predecessor[m-1] = m;
					decreasePriority(h, m-1, p[m-1]);
				}
				/*has a bottom neighbour*/
				if ((p[m] + A[m][m+Gsize] < p[m+Gsize]) && A[m][m+Gsize]) {
					p[m+Gsize] = A[m][m+Gsize] + p[m];
					predecessor[m+Gsize] = m;
					decreasePriority(h, m+Gsize, p[m+Gsize]);
				}
			}
			/*somewhere in the middle*/
			else {
				/*has a left neighbour*/
				if ((p[m] + A[m][m-1] < p[m-1]) && A[m][m-1]) {
					p[m-1] = A[m][m-1] + p[m];
					predecessor[m-1] = m;
					decreasePriority(h, m-1, p[m-1]);
				}
				/*has a bottom neighbour*/
				if ((p[m] + A[m][m+Gsize] < p[m+Gsize]) && A[m][m+Gsize]) {
					p[m+Gsize] = A[m][m+Gsize] + p[m];
					predecessor[m+Gsize] = m;
					decreasePriority(h, m+Gsize, p[m+Gsize]);
				}
				/*has a right neighbour*/
				if ((p[m] + A[m][m+1] < p[m+1]) && A[m][m+1]) {
					p[m+1] = A[m][m+1] + p[m];
					predecessor[m+1] = m;
					decreasePriority(h, m+1, p[m+1]);
				}
			}
		}
		/*node has no left neighbour*/
		else if ((m%Gsize) == 0) {
			/*first node in graph*/
			if (m == 0) {
				/*has a bottom neighbour*/
				if ((p[m] + A[m][m+Gsize] < p[m+Gsize]) && A[m][m+Gsize]) {
				p[m+Gsize] = A[m][m+Gsize] + p[m];
				predecessor[m+Gsize] = m;
				decreasePriority(h, m+Gsize, p[m+Gsize]);
				}
				/*has a right neighbour*/
				if ((p[m] + A[m][m+1] < p[m+1]) && A[m][m+1]) {
					p[m+1] = A[m][m+1] + p[m];
					predecessor[m+1] = m;
					decreasePriority(h, m+1, p[m+1]);
				}
			}
			/*first node on the last row*/
			else if (m == (GsizeSqr-Gsize)) {
				/*has a top neighbour*/
				if ((p[m] + A[m][m-Gsize] < p[m-Gsize]) && A[m][m-Gsize]) {
					p[m-Gsize] = A[m][m-Gsize] + p[m];
					predecessor[m-Gsize] = m;
					decreasePriority(h, m-Gsize, p[m-Gsize]);
				}
				/*has a right neighbour*/
				if ((p[m] + A[m][m+1] < p[m+1]) && A[m][m+1]) {
					p[m+1] = A[m][m+1] + p[m];
					predecessor[m+1] = m;
					decreasePriority(h, m+1, p[m+1]);
				}
			}
			/*anywhere in the middle*/
			else {
				/*has a top neighbour*/
				if ((p[m] + A[m][m-Gsize] < p[m-Gsize]) && A[m][m-Gsize]) {
					p[m-Gsize] = A[m][m-Gsize] + p[m];
					predecessor[m-Gsize] = m;
					decreasePriority(h, m-Gsize, p[m-Gsize]);
				}
				/*has a right neighbour*/
				if ((p[m] + A[m][m+1] < p[m+1]) && A[m][m+1]) {
					p[m+1] = A[m][m+1] + p[m];
					predecessor[m+1] = m;
					decreasePriority(h, m+1, p[m+1]);
				}
				/*has a bottom neighbour*/
				if ((p[m] + A[m][m+Gsize] < p[m+Gsize]) && A[m][m+Gsize]) {
				p[m+Gsize] = A[m][m+Gsize] + p[m];
				predecessor[m+Gsize] = m;
				decreasePriority(h, m+Gsize, p[m+Gsize]);
				}
			}
		}
	/*node on the right side of the graph (has no right neighbour)*/
	else if ((m%Gsize) == (Gsize-1)) {
			/*first node on the right side (i.e top-right)*/
			if (m == (Gsize-1)) {
				/*has a left neighbour*/
				if ((p[m] + A[m][m-1] < p[m-1]) && A[m][m-1]) {
					p[m-1] = A[m][m-1] + p[m];
					predecessor[m-1] = m;
					decreasePriority(h, m-1, p[m-1]);
				}
				/*has a bottom neighbour*/
				if ((p[m] + A[m][m+Gsize] < p[m+Gsize]) && A[m][m+Gsize]) {
					p[m+Gsize] = A[m][m+Gsize] + p[m];
					predecessor[m+Gsize] = m;
					decreasePriority(h, m+Gsize, p[m+Gsize]);
				}
			}
			/*last node of the graph*/
			else if (m == (GsizeSqr-1)) {
				/*has a left neighbour*/
				if ((p[m] + A[m][m-1] < p[m-1]) && A[m][m-1]) {
					p[m-1] = A[m][m-1] + p[m];
					predecessor[m-1] = m;
					decreasePriority(h, m-1, p[m-1]);
				}
				/*has a top neighbour*/
				if ((p[m] + A[m][m-Gsize] < p[m-Gsize]) && A[m][m-Gsize]) {
					p[m-Gsize] = A[m][m-Gsize] + p[m];
					predecessor[m-Gsize] = m;
					decreasePriority(h, m-Gsize, p[m-Gsize]);
				}
			}
			/*somewhere in the middle*/
			else {
				/*has a top neighbour*/
				if ((p[m] + A[m][m-Gsize] < p[m-Gsize]) && A[m][m-Gsize]) {
					p[m-Gsize] = A[m][m-Gsize] + p[m];
					predecessor[m-Gsize] = m;
					decreasePriority(h, m-Gsize, p[m-Gsize]);
				}
				/*has a left neighbour*/
				if ((p[m] + A[m][m-1] < p[m-1]) && A[m][m-1]) {
					p[m-1] = A[m][m-1] + p[m];
					predecessor[m-1] = m;
					decreasePriority(h, m-1, p[m-1]);
				}
				/*has a bottom neighbour*/
				if ((p[m] + A[m][m+Gsize] < p[m+Gsize]) && A[m][m+Gsize]) {
					p[m+Gsize] = A[m][m+Gsize] + p[m];
					predecessor[m+Gsize] = m;
					decreasePriority(h, m+Gsize, p[m+Gsize]);
				}
			}
		}
		/*node at the bottom of the graph (has no bottom neighbour)*/
		else if (m > ((GsizeSqr-Gsize)-1)) {
			if (m == (GsizeSqr-Gsize)) {
				/*has a top neighbour*/
				if ((p[m] + A[m][m-Gsize] < p[m-Gsize]) && A[m][m-Gsize]) {
					p[m-Gsize] = A[m][m-Gsize] + p[m];
					predecessor[m-Gsize] = m;
					decreasePriority(h, m-Gsize, p[m-Gsize]);
				}
				/*has a right neighbour*/
				if ((p[m] + A[m][m+1] < p[m+1]) && A[m][m+1]) {
					p[m+1] = A[m][m+1] + p[m];
					predecessor[m+1] = m;
					decreasePriority(h, m+1, p[m+1]);
				}
			}
			/*last node of the graph*/
			else if (m == (GsizeSqr-1)) {
				/*has a left neighbour*/
				if ((p[m] + A[m][m-1] < p[m-1]) && A[m][m-1]) {
					p[m-1] = A[m][m-1] + p[m];
					predecessor[m-1] = m;
					decreasePriority(h, m-1, p[m-1]);
				}
				/*has a top neighbour*/
				if ((p[m] + A[m][m-Gsize] < p[m-Gsize]) && A[m][m-Gsize]) {
					p[m-Gsize] = A[m][m-Gsize] + p[m];
					predecessor[m-Gsize] = m;
					decreasePriority(h, m-Gsize, p[m-Gsize]);
				}
			}
			/*somewhere in the middle*/
			else {
				/*has a left neighbour*/
				if ((p[m] + A[m][m-1] < p[m-1]) && A[m][m-1]) {
					p[m-1] = A[m][m-1] + p[m];
					predecessor[m-1] = m;
					decreasePriority(h, m-1, p[m-1]);
				}
				/*has a top neighbour*/
				if ((p[m] + A[m][m-Gsize] < p[m-Gsize]) && A[m][m-Gsize]) {
					p[m-Gsize] = A[m][m-Gsize] + p[m];
					predecessor[m-Gsize] = m;
					decreasePriority(h, m-Gsize, p[m-Gsize]);
				}
				/*has a right neighbour*/
				if ((p[m] + A[m][m+1] < p[m+1]) && A[m][m+1]) {
					p[m+1] = A[m][m+1] + p[m];
					predecessor[m+1] = m;
					decreasePriority(h, m+1, p[m+1]);
				}
			}
		}
		/*somewhere in the middle of the graph (will have all four neighbours)*/
		else {
				/*has a top neighbour*/
				if ((p[m] + A[m][m-Gsize] < p[m-Gsize]) && A[m][m-Gsize]) {
					p[m-Gsize] = A[m][m-Gsize] + p[m];
					predecessor[m-Gsize] = m;
					decreasePriority(h, m-Gsize, p[m-Gsize]);
				}
				/*has a right neighbour*/
				if ((p[m] + A[m][m+1] < p[m+1]) && A[m][m+1]) {
					p[m+1] = A[m][m+1] + p[m];
					predecessor[m+1] = m;
					decreasePriority(h, m+1, p[m+1]);
				}
				/*has a bottom neighbour*/
				if ((p[m] + A[m][m+Gsize] < p[m+Gsize]) && A[m][m+Gsize]) {
					p[m+Gsize] = A[m][m+Gsize] + p[m];
					predecessor[m+Gsize] = m;
					decreasePriority(h, m+Gsize, p[m+Gsize]);
				}
				/*has a left neighbour*/
				if ((p[m] + A[m][m-1] < p[m-1]) && A[m][m-1]) {
					p[m-1] = A[m][m-1] + p[m];
					predecessor[m-1] = m;
					decreasePriority(h, m-1, p[m-1]);
				}
			}
		}
		/*deallocate the memory used by the heap*/
		free(h);
		/*create a linked list of the shortest path from the initial to end point in the graph*/
		struct path_node *list = newPathNode(xf, yf);
		struct path_node *tmp = list;	/*temporary node to reference to the list*/
		j = xf + Gsize*yf;
		/*loop until initial position is not reached*/
		while (j != (xi + (Gsize)*yi)) {
			tmp->next = newPathNode(predecessor[j]%Gsize, predecessor[j]/Gsize);
			tmp = tmp->next;
			j = predecessor[j];
		}
		/*return the linked list just created*/
		return list;
}

