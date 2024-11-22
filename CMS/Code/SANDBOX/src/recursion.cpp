/* Implementation: Functions for File IO - Getting random messages from a file
*  By: Michael Galle

    Adapted by: Nigel Sinclair
                Rita Yevtushenko
                Fergus Page

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>			// Dynamic memory allocation for arrays that store quote location and length
#include <string.h>         // String operations.
#include "recursion.h"        // Include message header file. 

static link pHead, pTail;

// Assignment #2 - Recursive traverse functions

// Recursive Queue functions
link returnHead() {
	return pHead;
}

int count(link x) {
	if (x == NULL) return(0);
	return (1 + count(x->pNext));
}

link deleteR(link parent, link child, Item v) {
	if (child == NULL) return(NULL);
	if (child->Data.sid == v.sid) {
		parent->pNext = child->pNext;
		free(child);
		deleteR(parent, parent->pNext, v);
	}
	else {
		deleteR(child, child->pNext, v);
	}
	
	return 0;
}

void visit(link h) {
	printf("SID of node: %d\nMessage in the node: %s\n\n", h->Data.sid, h->Data.message);
}

void traverse(link h, void (*visit)(link)) {
	if (h == NULL) return;
	(*visit)(h);
	traverse(h->pNext, visit);
}

void traverseR(link h, void (*visit)(link)) {
	if (h == NULL) return;
	traverseR(h->pNext, visit);
	(*visit)(h);
}