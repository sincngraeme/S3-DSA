// main.cpp : Mainline for testing the Queue Functions
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Queues.h"

int main()
{
	link p, q; 
	int i; 

	InitQueue(); 

	// Create & Add Nodes numbered 1 to 10 to the Queue
	for (i = 0; i < 10; i++) {
		p = (link)malloc(sizeof(Node)); 
		p->Data.sid = i;                     // (*p).Data.sid = i;
		//(*p).Data.sid = i;
		AddToQueue(p);
	}

	while (!IsQueueEmpty()) {
		q = DeQueue(); 
		printf("\n SID of Node is: %d ", q->Data.sid);		// (*q).Data.sid
	}

	return(0);
}

