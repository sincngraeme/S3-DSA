/* message.cpp - Implementation for the message functions
 *
 * By Michael
 */

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <time.h>
#include "message.h"

int frandNum(int min, int max) {
	//srand(time(NULL));							// Remove this line - error in video - call srand( ) in main instead. 
	return((rand() % (max - min + 1)) + min);
}

int fnumQuotes(void) {
	FILE* fp;
	errno_t err; 
	char c; 
	int counter = -1;								// Counter = 0 ?

	if ((err = fopen_s(&fp, "FortuneCookies.txt", "r")) == 0) {
		printf("\nFile opened successfully \n");

		// Read file one character at a time 
		while ((c = fgetc(fp)) != EOF) {
			if (c == '%') {
				if (fgetc(fp) == '%') {
					counter++;
				}
			}
		}
		fclose(fp);
		return(counter); 
	}
	else {
		printf("\nError: Failed to open file\n"); 
		fclose(fp);
		return(-1);
	}

}


// Function returns an array that indicates the start of every quote in the file (number of characters from the start of the file) 
//long int* fquoteIndices(int numQuotes) {}

// Function returns the smaller of the actual quote length or MAX_QUOTE_LENGTH
//int* fquoteLengths(int numQuotes, long int* quoteIndices) {} 

// Function that gets q random quote from the FortuneCookies file 
//int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLengths) {}