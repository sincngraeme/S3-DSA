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
// int fnumQuotes(void) 
// {
//     printf("here\n");
//     int buf[2];                                 // string to store adjacent characters
//     int count = 0;

//     FILE* pfp = fopen(filePath, "r");            // file pointer to read file (previous)
//     FILE* cfp = pfp;                             // file pointer to read file (current)
//     fseek(cfp, 1, SEEK_SET);                     // sets character ahead


//     if((pfp == NULL) || (ferror(pfp) != 0))         // error checking (pfp and cpf are same)
//     {
//         perror("ERROR opening file");
//         return -1;
//     }

//     while(!ferror(cfp))      // cfp is further ahead
//     {
//         buf[0] = fgetc(pfp);
//         buf[1] = fgetc(cfp);

//         if(buf[0] == EOF || buf[1] == EOF)
//         {
//             break;
//         }

//         if((buf[0] == 37) && (buf[1] == 37)) 
//         {
//             printf("%d\n", count);
//             count++;             // if two adjacent characters are the same, check if they are both a %. if they are, increment
//         }
//     }
//     if(ferror(cfp))
//     {
//         perror("ERROR reading from file");
//     }

//     fclose(pfp);
//     fclose(cfp);

//     printf("number of quotes in file is: %d", count - 1);
//     return (count - 1);

// }

// Function to return the number of quotes in the file
int fnumQuotes(const char* filePath) 
{
    char buf[2];                                // buffer to store two consecutive characters
    int count = 0;                              // variable to count the number of quotes
 
    FILE* pfp = fopen(filePath, "r");           // open the file for reading
    if (pfp == NULL)                            // error checking
    {
        perror("ERROR opening file");
        return -1;
    }
 
    // Loop through the file character by character
    while (!feof(pfp)) 
    {
        buf[0] = fgetc(pfp);                    // read the first character
        if (buf[0] == '%')                      // if the first character is '%'
        {
            buf[1] = fgetc(pfp);                // read the next character
            if (buf[1] == '%')                  // if the second character is also '%'
            {
                count++;                        // increment the count for each %% pair
            }
        }
    }
 
    fclose(pfp);                                // close the file
 
    // Each quote is surrounded by %% (pair of percent symbols)
    // So, half of the count will give the number of quotes.
    int numQuotes = count / 2;
 
    printf("Number of quotes in file: %d\n", numQuotes);
    return numQuotes;
}



// Function returns an array that indicates the start of every quote in the file (number of characters from the start of the file) 
long int* fquoteIndices(int numQuotes) {}

// Function returns the smaller of the actual quote length or MAX_QUOTE_LENGTH
int* fquoteLength(int numQuotes, long int* quoteIndices) {} 

// Function that gets q random quote from the FortuneCookies file 
int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLengths) {}