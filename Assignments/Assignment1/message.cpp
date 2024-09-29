/* Implementation: Functions for File IO - Getting random messages from a file
*  By: Michael Galle
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>			// Dynamic memory allocation for arrays that store quote location and length
#include "message.h"

// Function gets a random number between min and max (max is the number of quotes in the file)
int frandNum(int min, int max) {}

// Function returns number of quotes in the file (only need to run once)
int fnumQuotes(void) 
{
    printf("here\n");
    char buf[3];                                 // string to store adjacent characters
    int count = 0;

    FILE* pfp = fopen(filePath, "r");            // file pointer to read file (previous)
    FILE* cfp = pfp + sizeof(char);                             // file pointer to read file (current)

    printf("%p\n%p\n",pfp,cfp);
    getchar();

    if((pfp == NULL) || (ferror(pfp) != 0))         // error checking (pfp and cpf are same)
    {
        perror("ERROR opening file");
        return -1;
    }
    printf("here2\n");

    while(cfp != NULL && !ferror(cfp))       // cfp is further ahead
    {
        buf[0] = fgetc(pfp);
        buf[1] = fgetc(cfp);

        if((buf[0] == '%') && (buf[1] == '%')) 
        {
            printf("%d", count);
            count++;             // if two adjacent characters are the same, check if they are both a %. if they are, increment
        }
        printf("a");
    }

    fclose(pfp);
    fclose(cfp);

    printf("number of quotes in file is: %d", count - 1);
    return (count - 1);

}

// Function returns an array that indicates the start of every quote in the file (number of characters from the start of the file) 
long int* fquoteIndices(int numQuotes) {}

// Function returns the smaller of the actual quote length or MAX_QUOTE_LENGTH
int* fquoteLength(int numQuotes, long int* quoteIndices) {} 

// Function that gets q random quote from the FortuneCookies file 
int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLengths) {}