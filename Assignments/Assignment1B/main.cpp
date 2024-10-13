/* main.cpp - Main file for testing the File IO functions that get random messages from a file 
*  By: Nigel Sinclair, Fergus Page, and Rita Yevtushenko
*  Adapted from code by Michael Galle
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>			// Needed for srand
#include "message.h"

int main() {

	int numQuotes;					// Number of quotes in the file
	long int* quoteIndices;			// Array of quote locations in the file (index correspondes to quote number)
	int* quoteLengths;				// Array of quote lengths (index correspondes to quote number)
	char testBuff[MAX_QUOTE_LENGTH] = "0"; // Buffer to write the message to
	int result;						 // result = 0 if successfully get a message
	link p, q; 
	int i; 

	
	// Count the number of quotes in the file and index it for fast access (only need to do this once) 
	numQuotes = fnumQuotes();									// Number of quotes
	quoteIndices = fquoteIndices(numQuotes);					// Index locations of the quotes
	quoteLengths = fquoteLength(numQuotes, quoteIndices);		// Length of each quote (up to MAX_QUOTE_LENGTH) - cut off after 	
  
	// // Get the random message from the file
	srand(time(NULL));					// Seed the random number generator
	int num = frandNum(0,numQuotes);
	result = GetMessageFromFile(testBuff, MAX_QUOTE_LENGTH, num, numQuotes, quoteIndices, quoteLengths);  // Later replace testBuff with 'node->msg.buff' which is a member of a node struct 
	printf("%d\t%d\t%d\n", num, quoteIndices[num], quoteLengths[num]);
	printf("-------------------------------------------------\n");
	printf("%s\n", testBuff);
	printf("-------------------------------------------------\n");

	system("pause");

	InitQueue(); 

		// Create & Add Nodes numbered 1 to 10 to the Queue
	for (i = 0; i < 10; i++) {
		p = (link)malloc(sizeof(Node)); 		
		p->Data.seqNum = i;                     // (*p).Data.sid = i;
		result = GetMessageFromFile(p->Data.message, MAX_QUOTE_LENGTH, frandNum(0,numQuotes), numQuotes, quoteIndices, quoteLengths);  // Later replace testBuff with 'node->msg.buff' which is a member of a node struct 
		if(result != 0)							// check the result of GetMessageFromFile
		{
			free(p);												
			break;								// we dont want to add if there is an error
		}
		AddToQueue(p);
		//free(p);
	}

	while (!IsQueueEmpty()) {
		q = DeQueue(); 
		printf("\n%d) %s", q->Data.seqNum, q->Data.message);		// print the data from each node
		free(q);													// data has been accessed so free q
	}

	free(quoteIndices);
	free(quoteLengths);

	return(0);
}
