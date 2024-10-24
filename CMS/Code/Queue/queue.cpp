#include "queue.h"
#include <stdlib.h>


static link pHead, pTail; 

void InitQueue(void) {
	pHead = pTail = NULL; 
}

int IsQueueEmpty(void) {
	return(pHead == NULL); 
}

void AddToQueue(link pn) {
	if (IsQueueEmpty()) {
		pHead = pTail = pn; 
	}
	else {
		pTail->pNext = pn;		// Old tail now points to pn (the node we added)
		pTail = pn;				// pTail points to pn
	}
	pTail->pNext = NULL;
}

link DeQueue(void) {
    link pTemp;					// Hold the current Head
	if (IsQueueEmpty()) {
		return(NULL);
	}
	else {
		pTemp = pHead;			// Store the current Head. pHead is returned and then incremented to next node in list
		pHead = pHead->pNext;	// pHead points to next Node in list, which becomes the new head
		return(pTemp);			// pTemp is original head, which gets returned
	}
}