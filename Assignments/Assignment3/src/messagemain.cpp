// main.cpp : Mainline for testing the Queue and Recursive Traverse functions - Assignment #2
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>			// Needed for srand
#include "message.h"

char* messagemain()
{
	messagelink q; 
	//clsint i; 
	int numQuotes;					// Number of quotes in the file
	long int* quoteIndices;			// Array of quote locations in the file (index correspondes to quote number)
	int* quoteLengths;				// Array of quote lengths (index correspondes to quote number)
	//char result;						// result = 0 if successfully get a message
	// Count the number of quotes in the file and index it for fast access (only need to do this once) 
	numQuotes = fnumQuotes();									// Number of quotes
	printf("%d", numQuotes);
	quoteIndices = fquoteIndices(numQuotes);					// Index locations of the quotes
	quoteLengths = fquoteLength(numQuotes, quoteIndices);		// Length of each quote (up to MAX_QUOTE_LENGTH) - cut off after 	
	
	printf("%ld", quoteIndices[4]);
	printf("%d", quoteLengths[4]);
  // // Get the random message from the file
	srand(time(NULL));					// Seed the random number generator

	// Create & Add Nodes numbered 1 to 10 to the Queue

	q = (messagelink)malloc(sizeof(Messagenode)); 
	GetMessageFromFile(q->Data.message, MAX_QUOTE_LENGTH, frandNum(0, numQuotes), MAX_QUOTE_LENGTH, quoteIndices, quoteLengths);  // Later replace testBuff with 'node->msg.buff' which is a member of a node struct 
	free(quoteIndices);
	free(quoteLengths);

	return(q->Data.message);
}

