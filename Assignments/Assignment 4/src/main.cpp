/* main.cpp - Main file for testing the File IO functions that get random messages from a file 
*  By: Michael Galle
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>			// Needed for srand
#include "message.h"
#include "Assignment4.h"

int main() {

	int numQuotes;					// Number of quotes in the file
	long int* quoteIndices;			// Array of quote locations in the file (index correspondes to quote number)
	int* quoteLengths;				// Array of quote lengths (index correspondes to quote number)
	char testBuff[MAX_QUOTE_LENGTH] = "0"; // Buffer to write the message to
	int result;						 // result = 0 if successfully get a message


	// Count the number of quotes in the file and index it for fast access (only need to do this once) 
	numQuotes = fnumQuotes();									// Number of quotes
	quoteIndices = fquoteIndices(numQuotes);					// Index locations of the quotes
	quoteLengths = fquoteLength(numQuotes, quoteIndices);		// Length of each quote (up to MAX_QUOTE_LENGTH) - cut off after 	
  
	// // Get the random message from the file
	srand(time(NULL));					// Seed the random number generator
	result = GetMessageFromFile(testBuff, MAX_QUOTE_LENGTH, frandNum(0,numQuotes), numQuotes, quoteIndices, quoteLengths);  // Later replace testBuff with 'node->msg.buff' which is a member of a node struct 
	printf("-------------------------------------------------\n");
	printf("%s\t\n", testBuff);
	printf("-------------------------------------------------\n");

	/*************************************************Assignment 4 Testing Case ***************************************************************/
	
	// Message for testing the compression
	unsigned char testMessage[] = "Hello World!";
	long long testLen = strlen((char*)testMessage);

	// Buffer for compression and decompression
	unsigned char compressedMessage[100]; // Buffer for compressed data
	unsigned char decompressedMessage[100]; // Buffer for the decompressed data

	// Compress the message
	long long compressedLen = RLEcompress(testMessage, testLen, compressedMessage, sizeof(compressedMessage));

	//Display the compressed message
	printf("Compressed message of length %llu", compressedLen);

	for (int i = 0; i < compressedLen; i++) {

		return(compressedMessage[i]);
	}

	// return (end1)

	// Decompress message
	long long decompressedLen = RLEdecompress(compressedMessage, compressedLen, decompressedMessage, sizeof(decompressedMessage), 0x1b);

	//Display the decompressed message
	printf("Decompressed message of length %llu", sizeof(decompressedLen));

	for (int i = 0; i < decompressedLen; i++) {

		return(decompressedMessage[i]);
	}
	// Check if the decompressed message matched with the original message
	if (decompressedLen == (long long)(testMessage && int (memcmp(testMessage, decompressedMessage, testLen) == 0))) {
		printf("Test Passed:");
	}
	else {
		printf("Test failed");
	}
	/******************************************************************************************************************************************/

	free(quoteIndices);
	free(quoteLengths);
	system("pause");
	return(0);
}