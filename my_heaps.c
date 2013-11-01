/*
  UTSC - CSC B63 - Winter 2012

  This is the implementation file for *YOUR* implementation of
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

#include <stdlib.h>
#include "my_heaps.h"

/*allocate a newNode*/
struct pq *newNode(int p, float w) {
	struct pq *n;
	n = (struct pq*)calloc(1, sizeof(struct pq));
	/*if (n == -1) {
		perror("calloc failed");
		exit(0);
	}*/
	n->priority = p;
	n->weight = w;
	return n;
}

/*check to see if the array is empty*/
int isEmpty(struct heap *h) {
	if (h->size == 1)	/*non-empty heap array*/
		return 1;
	return 0;
}

/*heapify*/
void heapify(struct heap *h, int i) {
	struct pq *tmp1, *tmp2;
	int j;
	/*Need to loop only till half of the heap array since last half contains only leaves*/
	for(j = i; j <= (((h->size)/2)+1); j++) {
		tmp1 = newNode(h->array[i]->priority, h->array[i]->weight);
		/*check to see if right child's weight is greater than the parent; if it is then swap*/
		if ((2*j+1 < h->size) && (h->array[i]->weight > h->array[(2*j)+1]->weight)) {
			/*check for right child since parent is greater*/
			if (h->array[2*j] >= (h->array[(2*j)+1])) {
				tmp2 = newNode(h->array[((2*j)+1)]->priority, h->array[(2*j)+1]->weight);
				h->array[(2*j)+1] = tmp1;
				h->array[j] = tmp2;
			}
			else {
				tmp2 = newNode(h->array[2*j]->priority, h->array[2*j]->weight);
				(h->array[2*j]) = tmp1;
				(h->array[j]) = tmp2;
			}
		}
		else if (2*j < (h->size)) {
			/*check for left child since parent is greater*/
			if (h->array[j]->weight > h->array[2*j]->weight) {
				tmp2 = newNode(h->array[2*j]->priority, h->array[2*j]->weight);
				h->array[2*j] = tmp1;
				h->array[j] = tmp2;
			}
		}
	}
}
		

/*percolate up in order to satisfy the min-heap property*/
void percolateUp(struct heap *h, int i) {
	struct pq *tmp1, *tmp2;
	int j;
	for(j = i; j > 1; j--) {
		/*check if child's weight is greater than its parent, if yes then swap them*/
		if (h->array[j]->weight < h->array[j/2]->weight) {
			tmp1 = newNode(h->array[j/2]->priority, h->array[j/2]->weight);
			tmp2 = newNode(h->array[j]->priority, h->array[j]->weight);
			h->array[j/2] = tmp2;
			h->array[j] = tmp1;
		}
	}
}

/*update the priority of a node n to the given priority w*/
void decreasePriority(struct heap *h, int n, float w) {
	int j;
	/*need to decrease priority for both Prim's and Djikstra's algorithm*/
	for(j = 1; j < (h->size); j++) {
		/*need to percolate up once we change node's weight*/
		if (n == h->array[j]->priority) {
			h->array[j]->weight = w;
			percolateUp(h, j);
			break;	/*need to break once we find the right node*/
		}
	}
}

/*build a heap from the given array of nodes*/
struct heap *buildHeap(int *p, float *q, int s) {
	int ASize = s + 1;
	struct pq **newP, *tmp;
	/*allocate memory*/
	newP = (struct pq**)calloc(ASize, sizeof(struct pq*));
	struct heap *h;
	/*allocate memory*/
	h = (struct heap*)calloc(ASize, sizeof(struct heap));
		
	h->size = ASize;
	h->array = newP;
	
	int i;
	for(i = 1; i < (h->size); i++) {
		tmp = newNode(p[i-1], q[i-1]);
		h->array[i] = tmp;
	}
	/*start from the 2nd half of the array for heapifying, if necessary*/
	int j;
	for (j = ((h->size)/2); j >= 1; j--) 
		heapify(h, i);
	/*return the new heap just created*/
	return h;
}

/*dequeue and return the dequeued element*/
int dequeue(struct heap *h) {
	struct pq *first, *last;
	/*store the first element*/
	first = h->array[1];
	last = h->array[h->size - 1];
	/*swap first element with last and heapify on first element*/
	h->array[1] = last;
	h->size -= 1;
	heapify(h, 1);
	return first->priority;
}

