// main.cpp : Mainline for testing the Queue and Recursive Traverse functions - Assignment #2
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>			// Needed for srand
#include "message.h"
// #include "recursion.h"

int main()
{
	link p, q; 
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
		p = (link)malloc(sizeof(Node)); 
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

	free(quoteIndices);
	free(quoteLengths);

	return(0);
}

