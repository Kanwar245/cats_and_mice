/*
  UTSC - CSC B63 - Winter 2012

  This is the header file for *YOUR* implementation of
  priority queues using heaps.

  You *must* implement heaps using arrays as discussed
  in class, and provide functions to carry out all
  heap operations as discussed in the handout.

  You are free to name your functions as you like and
  design your API (this is an important skill). Be sure
  to think through your design, so that it works well
  with the algorithms you will be coding later.

  Carefully comment and explain your code!

  F.J.E., March 2012
*/

#ifndef __heaps_header
#define __heaps_header
 
/*priority queue*/
struct pq{
	int priority;		/*priority of the PQ node*/
	float weight;		/*weight of the PQ node*/
};

/*heap array*/
struct heap{
	struct pq **array;		/*array to hold PQ nodes*/
	int size;				/*size of the heap array*/
};

/*allocate a newNode*/
struct pq *newNode(int p, float w);

/*check to see if the heap array is empty*/
int isEmpty(struct heap *h);

/*heapify (percolate down)*/
void heapify(struct heap *h, int i);

/*percolate up in order to satisfy the min-heap property*/
void percolateUp(struct heap *h, int i);

/*update the priority of a PQ node to the given priority*/
void decreasePriority(struct heap *h, int n, float w);

/*build a heap from the given array of node*/
struct heap *buildHeap(int *p, float *q, int s);

/*dequeue and return the dequeued element*/
int dequeue(struct heap *h);

#endif
