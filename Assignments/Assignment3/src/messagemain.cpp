// main.cpp : Mainline for testing the Queue and Recursive Traverse functions - Assignment #2
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>			//need for dynamic allocation of memory.
#include <time.h>			//needed for srand.
#include "message.h"		//message header.

const char* messagemain()	//old main function for messages, turned into a wrapper for FortuneCookies.txt access and random message delivery.
{
	messagelink q; 												// Messagelink instance q
	int numQuotes;												// Number of quotes in the file
	long int* quoteIndices;										// Array of quote locations in the file (index correspondes to quote number)
	int* quoteLengths;											// Array of quote lengths (index correspondes to quote number)
	numQuotes = fnumQuotes();									// Number of quotes
	quoteIndices = fquoteIndices(numQuotes);					// Index locations of the quotes
	quoteLengths = fquoteLength(numQuotes, quoteIndices);		// Length of each quote (up to MAX_QUOTE_LENGTH) - cut off after 	
	q = (messagelink)malloc(sizeof(Messagenode)); 				// Allocate memory for struct node q

	//assign a random message to message using getMessageFromFile
	const char* message = GetMessageFromFile(q->Data.message, MAX_QUOTE_LENGTH, frandNum(0, numQuotes), numQuotes, quoteIndices, quoteLengths);	

	free(quoteIndices);		// Now I'm Freeeeeeee
	free(quoteLengths);		// Freeeeee
	free(q);				// Memoryyyy

	return(message);		// Return the message to the call outside of the wrapper.
}