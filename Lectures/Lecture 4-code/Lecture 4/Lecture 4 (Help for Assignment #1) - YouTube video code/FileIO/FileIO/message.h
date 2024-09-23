/* message.h - Interface for the message functions
 * 
 * By Michael
 */

#pragma once
#define MAX_QUOTE_LENGTH 140

 // These functions will produce the inputs to the GetMessageFromFile() function
int frandNum(int min, int max);
int fnumQuotes(void);
//long int* fquoteIndices(int numQuotes); 
//int* fquoteLengths(int numQuotes, long int* quoteIndices); 


// Function that gets a random quote from FortuneCookies.txt
//int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLenghts ); 

