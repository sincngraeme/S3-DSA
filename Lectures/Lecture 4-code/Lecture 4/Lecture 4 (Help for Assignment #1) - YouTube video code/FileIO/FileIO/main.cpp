// main.cpp : Mainline to test fileIO functions
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <time.h>
#include "message.h"


int main()
{
    srand(time(NULL));                        // Seed the random number generator here (not in frandNum()) ***** Error in video **** 
    int numQuotes;

    // Count the number of quotes in the file (only need to do once) 
    numQuotes = fnumQuotes();
    printf("\nThere were %d quotes in the file \n", numQuotes);             // test
    printf("\nRandom quote number is: %d \n", frandNum(1, numQuotes));     // test

    /* ********************** Video instructions end here  ****************************/
    // Students need to continue development of additional functions fquoteIndices(), fquoteLengths() and GetMessageFromFile()
    
   
    //char testBuff[MAX_QUOTE_LENGTH];          // buffer to store quote retrieved from file
    //int result = 0;                           // result = 0 if no error in GetMessageFromFile()
    //int* quoteLengths;                        // Array of quote lengths (index corresponds to quote nunmber) 
    //long int* quoteIndices;                   // Array of quote locations in the file (index corresponds to quote number), location is number of bytes from start of file 
    
    //quoteIndices = fquoteIndices(numQuotes);  // Filename hardcoded in this function, pass numQuotes so can malloc() size of this array
    //quoteLengths = fquoteLengths(numQuotes, quoteIndices);  // Length of each quote (up to MAX_QUOTE_LENGTH), pass numQuotes so can malloc() size of this array 

    //result = GetMessageFromFile(testBuff, iLen, frandNum(1, numQuotes), numQuotes, quoteIndices, quoteLengths);

    // Notes: Later this will be combined with the Queues module and instead of using 'testBuff', students will add the quote to a node in a Queue


    system("pause");
    return(0);
}

