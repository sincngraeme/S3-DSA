/* Implementation: Functions for File IO - Getting random messages from a file
*  By: Michael Galle
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>			// Dynamic memory allocation for arrays that store quote location and length
#include "message.h"

// Function gets a random number between min and max (max is the number of quotes in the file)
//int frandNum(int min, int max) {}

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
    // So, half of the count will give the number of quotes.
    int numQuotes = count - 1;
 
    printf("Number of quotes in file: %d\n", numQuotes);
    return numQuotes;
}
// Function returns an array that indicates the start of every quote in the file (number of characters from the start of the file) 
long int* fquoteIndices(int numQuotes) 
{
    long int* indices = (long int*)malloc((numQuotes + 1) * sizeof(long int));                 // numQuotes is the number of indices in the array

    char buf[2];                                // buffer to store two consecutive characters

    FILE* fp = fopen(filePath, "r");

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
                /*TEMP*/printf("%d\t%d\n",i ,ftell(fp));
                indices[i] = ftell(fp);         // we are now at the begining of a quote set the given index of array to the current location of the file pointer
                i++;                            // increment the index since we have another quote
            }
        }
    }

    fclose(fp);

    return indices;
}

// Function returns the smaller of the actual quote length or MAX_QUOTE_LENGTH
int* fquoteLength(int numQuotes, long int* quoteIndices) 
{
    printf("Quote Lengths:\n\n");
    // we already know the start and end of each quote so we can find the length from there
    
    int* length = (int*)malloc(numQuotes * sizeof(int));                 

    for (int i = 0; i < numQuotes; i++) 
    {
        
        length[i] = (int)(quoteIndices[i + 1] - (quoteIndices[i] + 2));   
        printf("%d\t%d\n", i, length[i]);
    }

    return length;

} 

// Function that gets a random quote from the FortuneCookies file 
int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLengths) {}