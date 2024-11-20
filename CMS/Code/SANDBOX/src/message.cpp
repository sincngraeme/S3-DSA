/* Implementation: Functions for File IO - Getting random messages from a file
*  By: Michael Galle

    Adapted by: Nigel Sinclair
                Rita Yevtushenko
                Fergus Page

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>			// Dynamic memory allocation for arrays that store quote location and length
#include <string.h>         // String operations.
#include "message.h"        // Include message header file. 

static messagelink pHead, pTail; 

// Function gets a random number between min and max (max is the number of quotes in the file)
int frandNum(int min, int max) 
{
    return (rand() % (max - min) + min);
}

// Function returns number of quotes in the file (only need to run once)
int fnumQuotes() 
{
    char buf[2];                                // buffer to store two consecutive characters
    int count = 0;                              // variable to count the number of quotes

    FILE* fp = fopen(filePath, "r");           // open the file for reading

    if (fp == NULL)                            // error checking
    {
        perror("ERROR opening file");
        return -1;
    }
 
    // Loop through the file character by character
    while (!feof(fp)) 
    {
        buf[0] = fgetc(fp);                    // read the first character

        if (buf[0] == '%')                      // if the first character is '%'
        {
            buf[1] = fgetc(fp);                // read the next character

            if (buf[1] == '%')                  // if the second character is also '%'
            {
                count++;                        // increment the count for each %% pair
            }
        }
    }
 
    fclose(fp);                                // close the file
 
    // Each quote is surrounded by %% (pair of percent symbols)
    // So, the count minus 1 will give the number of quotes.
    int numQuotes = count - 1;
 
    //printf("Number of quotes in file: %d\n", numQuotes);        // Report number of quotes in the file.

    return numQuotes;
}
// Function returns an array that indicates the start of every quote in the file (number of characters from the start of the file) 
long int* fquoteIndices(int numQuotes) 
{
    long int* indices = (long int*)malloc((numQuotes + 1) * sizeof(long int));                 // numQuotes is the number of indices in the array
    char buf[2];                                // buffer to store two consecutive characters

    FILE* fp = fopen(filePath, "r");            // open file

    if (fp == NULL)                            // error checking
    {
        perror("ERROR opening file");
        free(indices);

        return NULL;
    }

    for (int i = 0; !feof(fp), i <= numQuotes;) 
    {
        buf[0] = fgetc(fp);                     // read the first character

        if (buf[0] == '%')                      // if the first character is '%'
        {
            buf[1] = fgetc(fp);                 // read the next character
            
            if (buf[1] == '%')                  // if the second character is also '%'
            {   
                indices[i] = ftell(fp);         // we are now at the begining of a quote set the given index of array to the current location of the file pointer
                i++;                            // increment the index since we have another quote
            }
        }
    }

    fclose(fp);                                 // close the file

    return indices;
}

// Function returns the smaller of the actual quote length or MAX_QUOTE_LENGTH
int* fquoteLength(int numQuotes, long int* quoteIndices) 
{
    //printf("Quote Lengths:\n\n");       // title

    // we already know the start and end of each quote so we can find the length from there
    
    int* length = (int*)malloc(numQuotes * sizeof(int));        // allocate space for the length storage array         

    for (int i = 0; i < numQuotes - 1; i++)                         // loop through all the quotes
    {             
        length[i] = (int)(quoteIndices[i + 1] - quoteIndices[i]) - 6;               // subract adjacent indices to find length (includes compensation for delimiting characters)
        length[i] = (length[i] >= MAX_QUOTE_LENGTH) ? MAX_QUOTE_LENGTH : length[i];     
        //^- if the length of the quote is greater than or equal to the space in the output buffer, use the length of the output buffer
        // - if the length of the quote is less than the space in the buffer, use the length of the quote
        //printf("%d\t%d\n", i, length[i]);       // print 'em
    }

    return length;
} 

// Function that gets a random quote from the FortuneCookies file 
int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLengths) 
{
    int mLen = quoteLengths[randNum];           // number of characters to read from file

    FILE* fp = fopen(filePath, "r");            // open file

    if (fp == NULL)                             // error checking
    {
        perror("ERROR opening file");       
        return -1;
    }    

    fseek(fp, quoteIndices[randNum], SEEK_SET);         // set file pointer to begining then offset by file index at randNum array index
    fread(buff, sizeof(char), mLen, fp);                // read message into buff as long as there is space and message
    buff[mLen] = '\0';                                  // make the last read character (either the last of the quote, or the last place in the buffer) a null terminating character
    
    if (mLen < iLen)                                        // if the length of the quote is less than the length of the output buffer,
    {
        for (int diff = iLen - mLen; diff >= -1; diff--)    // initialize a variable to represent the difference in length, and decrement it ever iteration of the for loop, as long as the difference is greater than or equal to -1
        {
            buff[iLen - diff] = '\0';                       // assign the null terminating character to the space in the buffer not occupied by the quote
        }
    } // set the last character in string to \0

   // printf("%d\n", randNum);
    fclose(fp);                                               // close the file

    return 0;
}


//STUFF FROM PART B

void InitQueue(void) {             
	pHead = pTail = NULL;          // initialize queue with null head and tail pointers
}

int IsQueueEmpty(void) {
	return(pHead == NULL);          // check if anything is in the queue. if there is, return 0, if it's empty, return 1.
}

void AddToQueue(messagelink pn) {          
	if (IsQueueEmpty()) {          
		pHead = pTail = pn;         // if the queue is empty, adding an element makes both the head and tail pointers point to the only element.
	}
	else {
		pTail->pNext = pn;		// Old tail now points to pn (the node we added)
		pTail = pn;				// pTail points to pn
	}
	pTail->pNext = NULL;        // make sure the tail's pNext points to null
}

messagelink DeQueue(void) {
	messagelink pTemp;					// Hold the current Head
	if (IsQueueEmpty()) {
		return(NULL);           // if the queue is empty, there is nothing to dequeue
	}
	else {
		pTemp = pHead;			// Store the current Head. pHead is returned and then incremented to next node in list
		pHead = pHead->pNext;	// pHead points to next Node in list, which becomes the new head
		return(pTemp);			// pTemp is original head, which gets returned
	}
}