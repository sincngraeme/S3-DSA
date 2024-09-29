/* main.cpp - Main file for testing the File IO functions that get random messages from a file 
*  By: Michael Galle
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>			// Needed for srand
#include "message.h"

int main() {

	int numQuotes;					// Number of quotes in the file
	long int* quoteIndices;			// Array of quote locations in the file (index correspondes to quote number)
	int* quoteLengths;				// Array of quote lengths (index correspondes to quote number)
	char testBuff[MAX_QUOTE_LENGTH]; // Buffer to write the message to
	int result;						 // result = 0 if successfully get a message


	// Count the number of quotes in the file and index it for fast access (only need to do this once) 
	numQuotes = fnumQuotes();									// Number of quotes
	// quoteIndices = fquoteIndices(numQuotes);					// Index locations of the quotes
	// quoteLengths = fquoteLength(numQuotes, quoteIndices);		// Length of each quote (up to MAX_QUOTE_LENGTH) - cut off after 	
  
	// // Get the random message from the file
	// srand(time(NULL));					// Seed the random number generator
	// result = GetMessageFromFile(testBuff, MAX_QUOTE_LENGTH, frandNum(1,numQuotes), numQuotes, quoteIndices, quoteLengths);  // Later replace testBuff with 'node->msg.buff' which is a member of a node struct 

	// system("pause");
	return(0);
}
