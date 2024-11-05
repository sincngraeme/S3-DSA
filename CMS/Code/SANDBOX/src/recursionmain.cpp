// main.cpp : Mainline for testing the Queue and Recursive Traverse functions - Assignment #2
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>			// Needed for srand
#include "recursion.h"
#include "message.h"

int main()
{
	messagelink p, q; 
	int i; 
	int numQuotes;					// Number of quotes in the file
	long int* quoteIndices;			// Array of quote locations in the file (index correspondes to quote number)
	int* quoteLengths;				// Array of quote lengths (index correspondes to quote number)
	int result;						// result = 0 if successfully get a message
	// Count the number of quotes in the file and index it for fast access (only need to do this once) 
	numQuotes = fnumQuotes();									// Number of quotes
	quoteIndices = fquoteIndices(numQuotes);					// Index locations of the quotes
	quoteLengths = fquoteLength(numQuotes, quoteIndices);		// Length of each quote (up to MAX_QUOTE_LENGTH) - cut off after 	
  // // Get the random message from the file
	srand(time(NULL));					// Seed the random number generator

	InitQueue(); 

	// Create & Add Nodes numbered 1 to 10 to the Queue
	for (i = 0; i < 10; i++) {
		p = (messagelink)malloc(sizeof(messageNode)); 
		result = GetMessageFromFile(p->Data.message, MAX_QUOTE_LENGTH, frandNum(0,numQuotes), numQuotes, quoteIndices, quoteLengths);  // Later replace testBuff with 'node->msg.buff' which is a member of a node struct 
		p->Data.seqNum = i;                     
		(*p).Data.sid = i;
		
		if(result != 0)							// check the result of GetMessageFromFile
		{
			free(p);												
			break;								// we dont want to add if there is an error
		}
		AddToQueue(p);
	}

	// Test count() 
	printf("\nThe number of nodes in the Queue is: %d\n", count(returnHead()));

	printf("\n\nTraversing list in forward direction gives ...\n");
	printf("\nThe sid is %d\n", p->Data.sid);
	traverse(returnHead(), visit); 
	printf("\n\nTraversing list in reverse direction gives ...\n");
	printf("\nThe sid is %d\n", p->Data.sid);
	traverseR(returnHead(), visit);
	
	// Test deleteR()
	Item v;
	v.sid = 7; 
	deleteR(returnHead(), returnHead()->pNext, v); 

	printf("\n\nThe number of nodes in the Queue after the deleteR() operation is: %d\n", count(returnHead()));

	// Empty  the Queue
	while (!IsQueueEmpty()) {
		q = DeQueue(); 
		printf("\n SID of Node is: %d, and its message is: %s", q->Data.sid, q->Data.message);		// (*q).Data.sid
	}


	// Test count() 
	printf("\n\nThe number of nodes in the Queue after dequeuing all nodes is: %d\n", count(returnHead()));

	free(quoteIndices);
	free(quoteLengths);

	return(0);
}

